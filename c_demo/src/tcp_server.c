/** @file tcp_socket.c
    @brief tcp socket
    @author Copyright (C) 2015 Richard.hmm <sunhyx@gmail.com>
*/

#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>

#include "debug.h"
#include "tcp_server.h"

#define MAX_BUFF_SIZE 100

typedef void sigfunc(INT32);

static void func_waitpid(INT32 signo)
{
	pid_t pid;
	INT32 stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		debug(LOG_ERR, "child %d exit", pid);
	}
	return;
}

static sigfunc* thread_signal(INT32 signo, sigfunc *func)
{
	struct sigaction act, oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (signo == SIGALRM)
	{
#ifdef            SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT; /* SunOS 4.x */
#endif
	}
	else
	{
#ifdef           SA_RESTART
		act.sa_flags |= SA_RESTART; /* SVR4, 4.4BSD */
#endif
	}
	if (sigaction(signo, &act, &oact) < 0)
	{
		return SIG_ERR;
	}
	return oact.sa_handler;
}

/**
 * @brief create_tcp_server
 * @param port
 * @return fd
 */
INT32 create_tcp_server(INT32 port, INT32 max_client_num)
{
	INT32 fd;
	INT32 rc;
	INT32 on = 1;
	struct sockaddr_in servaddr;

	/* Configure TCP Server */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	/* Create socket */
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		debug(LOG_ERR, "socket() failed");
		exit(-1);
	}

	/* Bind to socket */
	rc = bind(fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (rc < 0) {
		debug(LOG_ERR, "bind() failed");
		close(fd);
		exit(-1);
	}

	/* Listen on socket */
	listen(fd, max_client_num);
	debug(LOG_NOTICE, "max_client_num=%d\r\n", max_client_num);
	if (rc < 0) {
		debug(LOG_ERR, "listen() failed");
		close(fd);
		exit(-1);
	}

	return fd;
}

/**
 * @brief tcp_server_loop wait for client connection
 * @param port listenfd's port
 */
void tcp_server_loop(INT32 port)
{
	INT32 rc;
	INT32 listenfd;
	INT8 buffer[MAX_BUFF_SIZE];

	listenfd = create_tcp_server(port, 5);
	while (1) {
		INT32 clifd;
		struct sockaddr_in cliaddr;
		socklen_t clilen;

		clilen = sizeof(cliaddr);
		clifd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen); // blocking
		if (clifd < 0)
			continue;

		debug(LOG_NOTICE, "Connection established %s\r\n",
				inet_ntoa(cliaddr.sin_addr));

		while(1)
		{
			// something to read
			rc = recv(clifd, buffer, sizeof(buffer), 0);
			if (rc < 0) {
				if (errno != EWOULDBLOCK) {
					debug(LOG_ERR, " recv() failed");
					break;
				}
			} else if (rc == 0) {
				debug(LOG_NOTICE, "Connection closed\r\n");
				break;
			} else {
				debug(LOG_NOTICE, "recv() ok, rc = %d\r\n", rc);
				rc = send(clifd, buffer, rc, 0);
				if (rc < 0) {
					debug(LOG_ERR, "send() error\r\n");
					break;
				} else
					debug(LOG_NOTICE, "send() ok, rc = %d\r\n", rc);
			}
		}

		close(clifd);
		debug(LOG_NOTICE, "Connection closed %s\r\n", inet_ntoa(cliaddr.sin_addr));
	}
}

/**
 * @brief echo_request
 * @param arg
 */
static void *echo_request(void *fd)
{
	INT32 connfd = *((INT32 *)fd);
	INT8 buffer[MAX_BUFF_SIZE];
	INT32 rc;

	pthread_detach(pthread_self());

	while(1)
	{
		// echo
		rc = recv(connfd, buffer, sizeof(buffer), 0);
		if (rc > 0)
		{
			debug(LOG_NOTICE, "recv() ok, rc = %d\r\n", rc);
			rc = send(connfd, buffer, rc, 0);
			if (rc > 0)
				debug(LOG_NOTICE, "send() ok, rc = %d\r\n", rc);
			else
			{
				debug(LOG_ERR, "send() error\r\n");
				break;
			}
		}
		else if (rc == 0)
		{
			debug(LOG_NOTICE, "Connection closed\r\n");
			break;
		}
		else
		{
			debug(LOG_ERR, "recv() error\r\n");
			break;
		}
	}
	free(fd);
	close(connfd);
	pthread_exit(NULL);
}

/**
 * @brief tcp_server_pthread wait for client connection
 * @param port listenfd's port
 */
void tcp_server_pthread(INT32 port)
{
	INT32 rc;
	INT32 listenfd;
	INT8 buffer[MAX_BUFF_SIZE];
	INT32 *clifd;
	struct sockaddr_in cliaddr;
	socklen_t clilen;

	listenfd = create_tcp_server(port, 5);
	while (1) {
		pthread_t tid;

		clifd = (INT32 *)malloc(sizeof(INT32));
		clilen = sizeof(cliaddr);
		*clifd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen); // blocking
		if (*clifd < 0)
			continue;

		debug(LOG_NOTICE, "Connection established %s\r\n",
				inet_ntoa(cliaddr.sin_addr));

		if (0 != pthread_create(&tid, NULL, echo_request, clifd))
		{
			debug(LOG_ERR, "pthread_create\r\n");
			break;
		}

	}
}

/**
 * @brief do_echo echo request
 * @param userfd
 */
static void do_echo(INT32 userfd)
{
	INT8 buffer[MAX_BUFF_SIZE];
	INT32 rc;

	while(1)
	{
		// echo
		rc = recv(userfd, buffer, sizeof(buffer), 0);
		if (rc > 0)
		{
			debug(LOG_NOTICE, "recv() ok, rc = %d\r\n", rc);
			rc = send(userfd, buffer, rc, 0);
			if (rc > 0)
				debug(LOG_NOTICE, "send() ok, rc = %d\r\n", rc);
			else
			{
				debug(LOG_ERR, "send() error\r\n");
				break;
			}
		}
		else if (rc == 0)
		{
			debug(LOG_NOTICE, "Connection closed\r\n");
			break;
		}
		else
		{
			debug(LOG_ERR, "recv() error\r\n");
			break;
		}
	}

	close(userfd);
}

/**
 * @brief tcp_server_thread wait for client connection
 * @param port listenfd's port
 */
void tcp_server_thread(INT32 port)
{
	INT32 rc;
	INT32 listenfd;
	INT8 buffer[MAX_BUFF_SIZE];
	INT32 clifd;
	struct sockaddr_in cliaddr;
	socklen_t clilen;
	pid_t child_pid;

	thread_signal(SIGCHLD, &func_waitpid);

	listenfd = create_tcp_server(port, 5);
	while (1) {
		clilen = sizeof(cliaddr);
		clifd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen); // blocking
		if (clifd < 0)
			continue;

		debug(LOG_NOTICE, "Connection established %s\r\n",
				inet_ntoa(cliaddr.sin_addr));

		// create child thread to deal with tcp client session
		if (0 == safe_fork())
		{
			child_pid = getpid();
			debug(LOG_NOTICE, "child %d setup\r\n", child_pid);

			close(listenfd);  // close parent thread fd
			do_echo(clifd);
			exit(0);
		}
		close(clifd); // fork fail
	}
}

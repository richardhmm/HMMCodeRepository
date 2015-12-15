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

#include "debug.h"
#include "tcp_server.h"

#define MAX_BUFF_SIZE 100

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
 * @brief tcp_server wait for client connection
 * @param fd
 * @return result
 */
INT32 wait_connect(INT32 fd)
{
	fd_set fds;
	struct timeval timeout;
	INT32 rc;
	INT32 max_fd;
	FD_ZERO(&fds);
	max_fd = fd;
	FD_SET(fd, &fds);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	rc = select(max_fd + 1, &fds, NULL, NULL, &timeout);
	return rc;
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

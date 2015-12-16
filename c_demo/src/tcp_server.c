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

/**
 * @brief process_client echo request
 */
static void process_client(CLIENT * client, INT8 *buff, int len)
{
	INT32 rc;

	debug(LOG_NOTICE, "Received client( %s ) message: %s\n", client->name, buff);

	rc = send(client->fd, buff, len, 0);
	if (rc > 0)
		debug(LOG_NOTICE, "send() ok, rc = %d, send_buff: %s\r\n", rc, buff);
	else
	{
		debug(LOG_ERR, "send() error\r\n");
	}
}

/**
 * @brief tcp_server_select wait for client connection
 * @param port listenfd's port
 */
void tcp_server_select(INT32 port)
{
	INT32 rc;
	INT8 buffer[MAX_BUFF_SIZE];
	struct sockaddr_in cliaddr;
	INT32 i, maxi, maxfd, sockfd;
	INT32 nready;
	INT32 n;
    fd_set rset, allset;        // select file set
    INT32 listenfd, connectfd;    //socket fd
    CLIENT client[FD_SETSIZE];  //FD_SETSIZE为select函数支持的最大描述符个数
    INT32 sin_size;               //地址信息结构体大小

	listenfd = create_tcp_server(port, 5);
	INT32 opt = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //设置socket属性

	//初始化select
	maxfd = listenfd;
	maxi = -1;
	for (i = 0; i < FD_SETSIZE; i++)
	{
		client[i].fd = -1;
	}
	FD_ZERO(&allset);           //清空
	FD_SET(listenfd, &allset);  //将监听socket加入select检测的描述符集合

    while (1)
	{
		rset = allset;
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);    //调用select
		debug(LOG_NOTICE, "Select() and the return num is %d. \n", nready);

		if (FD_ISSET(listenfd, &rset))
		{                       //检测是否有新客户端请求
			debug(LOG_NOTICE, "Accept a connection.\n");

			//调用accept，返回服务器与客户端连接的socket描述符
			sin_size = sizeof(struct sockaddr_in);
			if ((connectfd = accept(listenfd, (struct sockaddr *) &cliaddr,
					(socklen_t *) &sin_size)) == -1)
			{
				debug(LOG_ERR, "Accept() error\n");
				continue;
			}

			//将新客户端的加入数组
			for (i = 0; i < FD_SETSIZE; i++)
			{
				if (client[i].fd < 0)
				{
					char buffer[20];
					client[i].fd = connectfd;   //保存客户端描述符
					memset(buffer, '0', sizeof(buffer));
					sprintf(buffer, "Client[%.2d]", i);
					memcpy(client[i].name, buffer, strlen(buffer));
					client[i].addr = cliaddr;
					memset(buffer, '0', sizeof(buffer));
					sprintf(buffer, "Only For Test!");
					memcpy(client[i].data, buffer, strlen(buffer));
					debug(LOG_NOTICE, "You got a connection from %s:%d.\n",
							inet_ntoa(client[i].addr.sin_addr),
							ntohs(client[i].addr.sin_port));
					debug(LOG_NOTICE, "Add a new connection:%s\n", client[i].name);
					break;
				}
			}

			if (i == FD_SETSIZE)
				debug(LOG_NOTICE, "Too many clients\n");

			FD_SET(connectfd, &allset); //将新socket连接放入select监听集合
			if (connectfd > maxfd)
				maxfd = connectfd;  //确认maxfd是最大描述符
			if (i > maxi)       //数组最大元素值
				maxi = i;
			if (--nready <= 0)
				continue;       //如果没有新客户端连接，继续循环
		}

		for (i = 0; i <= maxi; i++)
		{
			if ((sockfd = client[i].fd) < 0)    //如果客户端描述符小于0，则没有客户端连接，检测下一个
				continue;

			// 有客户连接，检测是否有数据
			if (FD_ISSET(sockfd, &rset))
			{
				debug(LOG_NOTICE, "Receive from connect fd[%d].\n", i);
				if ((n = recv(sockfd, buffer, MAX_BUFF_SIZE, 0)) == 0)
				{               //从客户端socket读数据，等于0表示网络中断
					close(sockfd);  //关闭socket连接
					debug(LOG_ERR, "%s closed. User's data: %s\n", client[i].name,
							client[i].data);
					FD_CLR(sockfd, &allset);    //从监听集合中删除此socket连接
					client[i].fd = -1;  //数组元素设初始值，表示没客户端连接
				}
				else
					process_client(&client[i], buffer, n); //接收到客户数据，开始处理

				if (--nready <= 0)
					break;      //如果没有新客户端有数据，跳出for循环回到while循环
			}
		}
	}
	close(listenfd);            //关闭服务器监听socket
}

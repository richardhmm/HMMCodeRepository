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

#include "debug.h"
#include "tcp_socket.h"

/**
 * @brief create_tcp_server
 * @param port
 * @return fd
 */
INT32 create_tcp_server(INT32 port)
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

	/* Set address reuse enable */
	rc = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (INT8 *) &on, sizeof(on));
	if (rc < 0) {
		debug(LOG_ERR, "setsockopt() failed");
		close(fd);
		exit(-1);
	}

	/* Set non blocking */
	rc = ioctl(fd, FIONBIO, (INT8 *) &on);
	if (rc < 0) {
		debug(LOG_ERR, "ioctl() failed");
		close(fd);
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
	listen(fd, 1);
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
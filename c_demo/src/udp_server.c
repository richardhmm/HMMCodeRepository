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
#include "udp_server.h"

#define MAX_UDP_BUFF_SIZE 100

/**
 * @brief create_udp_server
 * @param port
 * @return fd
 */
INT32 create_udp_server(INT32 port)
{
	INT32 fd;
	INT32 rc;
	struct sockaddr_in servaddr;

	/* Configure UDP Server */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	/* Create udp socket */
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		debug(LOG_ERR, "UDP socket() failed");
		exit(-1);
	}

	/* Bind to socket */
	rc = bind(fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if (rc < 0) {
		debug(LOG_ERR, "bind() failed");
		close(fd);
		exit(-1);
	}

	debug(LOG_INFO, "UDP sever create ok");
	return fd;
}

/**
 * @brief udp_server_loop wait for client connection
 * @param port listenfd's port
 */
void udp_server_loop(INT32 port)
{
	INT32 size, num, i;
	INT32 fd;
	INT8 buffer[MAX_UDP_BUFF_SIZE];
	struct sockaddr_in cliaddr;

	size = sizeof(struct sockaddr_in);
	fd = create_udp_server(port);
	while (1) {
		num = recvfrom(fd, buffer, MAX_UDP_BUFF_SIZE, 0, (struct sockaddr *)&cliaddr, &size);
		if (num < 0)
		{
			debug(LOG_ERR, "recvfrom() failed");
			close(fd);
			exit(-1);
		}
		debug(LOG_INFO, "recvfrom num=%d", num);
		for(i = 0; i < num; i++)
		{
			debug(LOG_INFO, "buffer[%d]=0x%x", i, buffer[i]);
		}

		// send to udp client
		sendto(fd, buffer, num, 0, (struct sockaddr *)&cliaddr, size);
	}
	close(fd);
}

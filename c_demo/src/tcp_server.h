
/**
 * @file tcp_server.h
 * @brief  tcp socket
 */

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "types.h"

/**
 * @brief create_tcp_server
 * @param port
 * @return fd
 */
INT32 create_tcp_server(INT32 port);

/**
 * @brief tcp_server wait for client connection
 * @param fd
 * @return result
 */
INT32 wait_connect(INT32 fd);

/**
 * @brief tcp_server_loop wait for client connection
 * @param port listenfd's port
 */
void tcp_server_loop(INT32 port);

#endif /* _TCP_SERVER_H_ */

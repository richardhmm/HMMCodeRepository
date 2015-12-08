
/**
 * @file tcp_socket.h
 * @brief  tcp socket
 */

#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

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

#endif /* _TCP_SOCKET_H_ */

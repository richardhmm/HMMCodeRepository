
/**
 * @file udp_server.h
 * @brief  udp server
 */

#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include "types.h"

/**
 * @brief create_udp_server
 * @param port
 * @return fd
 */
INT32 create_udp_server(INT32 port);

/**
 * @brief udp_server_loop wait for client connection
 * @param port listenfd's port
 */
void udp_server_loop(INT32 port);

#endif /* _UDP_SERVER_H_ */

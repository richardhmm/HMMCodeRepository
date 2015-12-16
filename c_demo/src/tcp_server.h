
/**
 * @file tcp_server.h
 * @brief  tcp socket
 */

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "types.h"

#define MAX_STRING_LEN  30
#define MAX_BUFF_SIZE      320

typedef struct _CLIENT
{
    int fd;                     //客户端socket描述符
    char name[MAX_STRING_LEN];              //客户端名称
    struct sockaddr_in addr;    //客户端地址信息结构体
    char data[MAX_BUFF_SIZE];     //客户端私有数据指针
} CLIENT;

/**
 * @brief create_tcp_server
 * @param port
 * @return fd
 */
INT32 create_tcp_server(INT32 port, INT32 max_client_num);

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

/**
 * @brief tcp_server_pthread wait for client connection
 * @param port listenfd's port
 */
void tcp_server_pthread(INT32 port);

#endif /* _TCP_SERVER_H_ */

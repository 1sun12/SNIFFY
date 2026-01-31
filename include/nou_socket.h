/**
 * @file nou_socket.h
 * @brief Abstracting network operations
 */
#ifndef NOU_SOCKET_H
#define NOU_SOCKET_H

/**
 * @brief User headers:
 * - debug.h    |   helpful debugging macros
 */
#include "debug.h"

/**
 * @brief General headers:
 * - stdio.h    |   Standard I/O (printf, fprintf, FILE operations)
 * - stdlib.h   |   General utilities (malloc, free, exit, atoi)
 * - string.h   |   String operations (memset, memcpy, strcmp, strlen)
 * - unistd.h   |   Unix standard (close, read, write, fork, getpid)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Network headers:
 * - sys/socket.h           |   Core socket API (socket, bind, listen, accept, send, recv)
 * - sys/types.h            |   System call data types (size_t, ssize_t, pid_t)
 * - netdb.h                |   Network database operations (getaddrinfo, getnameinfo, struct addrinfo)
 * - netinet/if_ether.h     |   Ethernet header (ETH_P_ALL)
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/if_ether.h>

/**
 * @brief Represents a socket & the address information used to template it + other goodies
 */
typedef struct {
    int sockfd;
    struct addrinfo hints;
} nou_socket;

/** 
 * ==========================================================================
 * Constructor & Destructor - Initialize and freeing "this" object
 * ==========================================================================
 * @note First param is always "this" object (self)
 */

/**
 * @brief Creates and initializes a nou socket (constructor)
 * @return Pointer to nou socket, or NULL on failure
 */
nou_socket *nou_socket_create();

/**
 * @brief Destroys and frees a nou socket (destructor)
 * @param self `This` object
 */
void nou_socket_destroy(nou_socket **self); 

/**
 * ==========================================================================
 * METHODS - Functions that operate on the object
 * ==========================================================================
 * @note First param is always "this" object (self)
 */
 
/**
 * @details Inside of addrinfo:
 * - int ai_flags               |   Behavior modifier for getaddrinfo()     |   AI_PASSIVE, AI_CANONNAME
 * - int ai_family              |   Address / Protocol family               |   AF_UNSPEC, AF_INET, AF_INET6
 * - int ai_socktype            |   Socket type (transport layer behavior)  |   SOCK_STREAM, SOCK_DGRAM, SOCK_RAW
 * - int ai_protocol            |   Specific proto. within the family       |   just set to "0" for any
 * - size_t ai_addrlen          |   Size of the socket address structure    |   essential for bind, connect, and send, but not recieving
 * - struct sockaddr *ai_addr   |   Pointer to the actual socket address    |   Contains the IP and Port (filled in by getaddrinfo)
 * - char *ai_canonname         |   Canonical hostname                      |   ai_flags = AI_CANONNAME, then this points to a string containing official name of host
 * - strut addrinfo *ai_next    |   Linked list pointer                     |   Points to the next address from the linked-list returned by getaddrinfo()
 * 
 * @param self `This` object
 */
void fill_out_hints(nou_socket *self);

#endif
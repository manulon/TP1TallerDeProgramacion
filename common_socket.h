#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

//Basado en ej de clase de Ezequiel Werner.

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <netdb.h>
#include <errno.h>

#define FAMILY AF_INET
#define PROTOCOL 0
#define SOCK_TYPE SOCK_STREAM
#define SERVER_FLAGS AI_PASSIVE
#define CLIENT_FLAGS 0

typedef struct {
    int fd;
} socket_t;

void socket_init(socket_t *self, int family, int socktype, int protocol);

void socket_uninit(socket_t *self);

bool socket_bind_and_listen(socket_t *self,
                            const char *hostname,
                            const char *servicename);

int socket_accept
(socket_t *listener, socket_t *peer);

void socket_connect
(socket_t *self, const char* hostname, const char* servicename);

ssize_t socket_receive
(socket_t *self, unsigned char *buffer, size_t length);

#endif

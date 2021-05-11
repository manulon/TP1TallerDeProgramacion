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

//Inicializa un socket con su file descriptor asociado.
void socket_init(socket_t *self, int family, int socktype, int protocol);

//Cierra el socket.
//Pre: se ha inicializado un socket.
//Post: se lo cierra cierra y se hace un shutdown de este.
void socket_uninit(socket_t *self);

//Devuelve true si pudo conectarse a un puerto y 
//activarse para recibir conexiones,
//false en caso de error.
bool socket_bind_and_listen(socket_t *self,
                            const char *hostname,
                            const char *servicename);


//Acepta una conexion y devuelve el fd en caso exitoso, -1 en caso de error.
int socket_accept
(socket_t *listener, socket_t *peer);

//Conecta al socket.
void socket_connect
(socket_t *self, const char* hostname, const char* servicename);

//Recibe una cantidad length de bytes.
//Post: Devuelve la cantidad de bytes recibidos.
ssize_t socket_receive
(socket_t *self, unsigned char *buffer, size_t length);

#endif

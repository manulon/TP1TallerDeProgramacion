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
void socket_init(socket_t *self, int fd);

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

//Devuelve una lista de posibles direcciones para conectarse.
struct addrinfo* get_address_info
(socket_t* self, const char* host, const char* service, int flags);

//Acepta una conexion y devuelve el fd en caso exitoso, -1 en caso de error.
int socket_accept
(socket_t *listener, socket_t *peer);

//Devuelve un booleano que dice si la conexion fue exitosa o no.
void socket_connect
(socket_t *self, const char* hostname, const char* servicename);

ssize_t socket_send_message
(socket_t* self, unsigned char* msg, int size);
ssize_t socket_send_size
(socket_t* self, short int size);


ssize_t socket_receive
(socket_t *self, unsigned char *buffer, size_t length);

void _socket_short_to_char(short int size, unsigned char* buffer);
short int _socket_char_to_short(unsigned char* buffer);

#endif

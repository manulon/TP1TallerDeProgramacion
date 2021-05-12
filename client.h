#ifndef CLIENT_H
#define CLIENT_H

#include "common_socket.h"

typedef struct {
    const char* hostname;
    const char* servicename;
    const char* filename;
    unsigned char* message;
    int message_length;
}client_t;

void client_init
(client_t* self, char** argv);

void client_uninit
(client_t* self);

void client_communicate_with_server
(client_t* self,socket_t* socket);

void _client_decrypt_message
(client_t* self);

void _client_print_message
(client_t* self);

void client_init_connection
(client_t* self,socket_t* socket);

void client_uninit_connection
(client_t* self,socket_t* socket);

void client_set_message_length
(client_t* self, int len);

void client_set_message
(client_t* self, unsigned char* msg);

unsigned char* client_get_message
(client_t* self);

int client_get_message_length
(client_t* self);

#endif

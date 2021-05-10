#ifndef COMMON_COMMUNICATION_PROTOCOL_H
#define COMMON_COMMUNICATION_PROTOCOL_H

#include "common_socket.h"

typedef struct{
    socket_t* socket;
}communication_protocol_t;

void communication_protocol_init
(communication_protocol_t* self, socket_t* socket);

void communication_protocol_uninit
(communication_protocol_t* self);

ssize_t communication_protocol_send_message
(communication_protocol_t* self, unsigned char* msg, int length);

ssize_t _send_size
(communication_protocol_t* self, int size);

ssize_t _send_message
(communication_protocol_t* self, unsigned char* msg, int size);

int communication_protocol_receive_size
(communication_protocol_t* self);

ssize_t communication_protocol_receive_message
(communication_protocol_t* self, int length, unsigned char* buffer);

#endif

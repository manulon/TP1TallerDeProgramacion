#include "common_communication_protocol.h"

void communication_protocol_init
(communication_protocol_t* self, socket_t* socket){
    self->socket = socket;
}

void communication_protocol_uninit
(communication_protocol_t* self){}

ssize_t communication_protocol_send_message
(communication_protocol_t* self, unsigned char* msg, int length){
    ssize_t total_bytes_sent = 0;
    _send_size(self,length);
    _send_message(self,msg,length);
    return total_bytes_sent;
}

ssize_t _send_size
(communication_protocol_t* self, int size){
    ssize_t bytes_sent = 0;
    bytes_sent = socket_send_size(self->socket,(short int)size);
    return bytes_sent;
}

ssize_t _send_message
(communication_protocol_t* self, unsigned char* msg, int size){
    ssize_t bytes_sent = 0;
    bytes_sent = socket_send_message(self->socket,msg,size);
    return bytes_sent;
}

int communication_protocol_receive_size
(communication_protocol_t* self){
    unsigned char buffer[2] = "";                    

    socket_receive(self->socket, buffer, 2);

    short int size = _socket_char_to_short(buffer);
    return size;
}

ssize_t communication_protocol_receive_message
(communication_protocol_t* self, int length, unsigned char* buffer){
    ssize_t bytes_received = 0;
    bytes_received = socket_receive(self->socket,buffer,length);  

    return bytes_received;
}

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
    int remaining_bytes = 2;       
    int total_bytes_sent = 0;
    unsigned char buffer[2];

    _socket_short_to_char(size,buffer);

    if (size == 0){
        return total_bytes_sent;
    } 

    while (total_bytes_sent < 2) {
        ssize_t bytes = send(self->socket->fd, 
                            &buffer[total_bytes_sent],
                            remaining_bytes, MSG_NOSIGNAL);
        
        if (bytes == -1) {
			fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_sent;
}

ssize_t _send_message
(communication_protocol_t* self, unsigned char* msg, int size){
    int remaining_bytes = size;
    int total_bytes_sent = 0;

    if (size == 0){
        return total_bytes_sent;
    }

    while (total_bytes_sent < size) {
        ssize_t bytes = send(self->socket->fd, 
                            &msg[total_bytes_sent], 
                             remaining_bytes, MSG_NOSIGNAL);
    
        if (bytes == -1) {
			fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_sent;
}

int communication_protocol_receive_size
(communication_protocol_t* self){
    unsigned char buffer[2] = "";                    
    int remaining_bytes = 2;
    int total_bytes_received = 0;

    while (total_bytes_received < 2) {
        ssize_t bytes = recv(self->socket->fd, &buffer[total_bytes_received],
                        remaining_bytes, 0);
        if (bytes == -1) {
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }

    int size = _socket_char_to_short(buffer);

    return size;

}

ssize_t communication_protocol_receive_message
(communication_protocol_t* self, int length, unsigned char* buffer){
    if (length == 0){ return 0; }
    int remaining_bytes = length;
    int total_bytes_received = 0;

    while (total_bytes_received < length) {
        ssize_t bytes = recv(self->socket->fd, &buffer[total_bytes_received],
                        remaining_bytes, 0);
        if (bytes == -1) {
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
            return bytes;
        }
        if (bytes == 0) break;
        
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_received;
}

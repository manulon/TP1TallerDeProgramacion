#include "client.h"
#include "client_file_reader.h"

void client_init(client_t* self, char** argv){
    self->hostname = argv[1];
    self->servicename = argv[2];
    self->filename = argv[3];
    self->message_length = 0;

    _client_read_plaintext_from_file(self);
}

void client_uninit(client_t* self){
    free(self->message);
}

void _client_read_plaintext_from_file(client_t* self){
    file_reader_t file_reader;
    file_reader_init(&file_reader, self->filename);
    file_reader_read_chunk(&file_reader,self);
    file_reader_uninit(&file_reader);
}

void client_send_message_to_server(client_t* self, socket_t* peer){
    socket_connect(peer,self->hostname,self->servicename);

    socket_send_size(peer,(short int)self->message_length);
    socket_send_message(peer,self->message,self->message_length);

    free(self->message);
    
}

void client_receive_encrypted_message_from_server(client_t* self, socket_t* peer){
    _client_receive_size(self,peer);
    _client_receive_message(self,peer);
}

void _client_receive_message(client_t* self, socket_t* peer){
    char buffer[MAX_LINE_SIZE];
    ssize_t bytes_received = 0;
    
    bytes_received = socket_receive(peer, buffer, self->message_length);
        
    self->message = (char *)malloc( (self->message_length) * sizeof(char));

    for(int i=0 ; i < bytes_received ; i++){
        self->message[i] = buffer[i];
    }
}

void _client_receive_size(client_t* self, socket_t* peer){
    char buffer[2];                     //constante ¡?¡?

    socket_receive(peer, buffer, 2);
    
    short int size = _socket_char_to_short(buffer);

    self->message_length = size;
}

void client_decrypt_message(client_t *self){
    for(int i=0; i<self->message_length; i++){
        self->message[i] += 65;
    }
}
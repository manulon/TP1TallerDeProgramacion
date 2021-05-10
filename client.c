#include "client.h"
#include "client_file_reader.h"
#include "client_protocol.h"

void client_init(client_t* self, char** argv){
    self->hostname = argv[1];
    self->servicename = argv[2];
    self->filename = argv[3];
    self->message_length = 0;
}

void client_init_connection(client_t* self,socket_t* socket){
    socket_connect(socket,self->hostname,self->servicename);
}

void client_uninit(client_t* self){}

void client_communicate_with_server(client_t* self,socket_t* socket){
    file_reader_t file_reader;
    client_protocol_t protocol;

    file_reader_init(&file_reader, self->filename);
    client_protocol_init(&protocol,socket,self);

    while(file_reader_read_chunk(&file_reader,self)){
        client_protocol_start(&protocol);
        _client_decrypt_message(self);
        _client_print_message(self);
    }
    
    client_protocol_uninit(&protocol);
    file_reader_uninit(&file_reader);
}

void _client_decrypt_message(client_t *self){
    for ( int i=0 ; i<self->message_length ; i++ ){ 
        self->message[i] = (self->message[i]) + 65;
    }
}

void _client_print_message(client_t* self){
    self->message[self->message_length] = 10;
    fwrite(self->message, sizeof(unsigned char),
    (self->message_length+1), stdout);
     
    free(self->message);
}

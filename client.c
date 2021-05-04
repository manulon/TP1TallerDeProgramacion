#include "client.h"
#include "client_file_reader.h"

void client_init(client_t* self, char** argv){
    self->hostname = argv[1];
    self->servicename = argv[2];
    self->filename = argv[3];
    self->message_length = 0;
}

void client_init_connection(client_t* self,socket_t* socket){
    socket_connect(socket,self->hostname,self->servicename);
}

void client_uninit(client_t* self){
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
}

void client_send_message_to_server(client_t* self,socket_t* socket){
    file_reader_t file_reader;
    file_reader_init(&file_reader, self->filename);
    file_reader_iterator(&file_reader,self,socket);
    file_reader_uninit(&file_reader);
}

void client_receive_encrypted_message_from_server
(client_t* self, socket_t* peer){
    _client_receive_size(self,peer);
    _client_receive_message(self,peer);
}

ssize_t _client_receive_message(client_t* self, socket_t* peer){
    unsigned char buffer[MAX_LINE_SIZE];
    ssize_t bytes_received = 0;
    bytes_received = socket_receive(peer, buffer, self->message_length);  
    self->message = (unsigned char *)malloc
    ( (self->message_length+2) * sizeof(unsigned char));

    for ( int i = 0 ; i < bytes_received ; i++ ){
        self->message[i] = buffer[i];
    }

    self->message[self->message_length+1] = 0;

    return bytes_received;
}

ssize_t _client_receive_size(client_t* self, socket_t* peer){
    unsigned char buffer[2];                     //constante ¡?¡?
    ssize_t bytes_received;

    bytes_received = socket_receive(peer, buffer, 2);

    short int size = _socket_char_to_short(buffer);
    self->message_length = size;
    return bytes_received;
}

void client_decrypt_message(client_t *self){
    for ( int i=0 ; i<self->message_length ; i++ ){ 
        self->message[i] = (self->message[i]) + 65;
    }
}

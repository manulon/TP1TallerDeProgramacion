#include "client_protocol.h"
#include "client.h"
#include "common_communication_protocol.h"

void client_protocol_init
(client_protocol_t* self, socket_t* socket,client_t* client){
    self->socket = socket;
    self->client = client;
}

void client_protocol_start(client_protocol_t* self){
    communication_protocol_t comm;
    communication_protocol_init(&comm, self->socket);
    _client_protocol_send_message(self,&comm);
    free(self->client->message);
    _client_protocol_receive_message(self,&comm);
    communication_protocol_uninit(&comm);
}

void client_protocol_uninit
(client_protocol_t* self){
    //cierro el socket o no es necesario?????
}

void _client_protocol_send_message
(client_protocol_t* self, communication_protocol_t* comm){
    communication_protocol_send_message
    (comm, client_get_message(self->client), 
    client_get_message_length(self->client));
}

ssize_t _client_protocol_receive_message
(client_protocol_t* self, communication_protocol_t* comm){
    ssize_t bytes_received = 0;
    int new_length = 0;

    new_length = communication_protocol_receive_size(comm);
    client_set_message_length(self->client,new_length);
    
    unsigned char* msg_aux;
    msg_aux = calloc(self->client->message_length+1,sizeof(char));

    communication_protocol_receive_message(comm,self->client->message_length,msg_aux);
    
   self->client->message = calloc(self->client->message_length+1,sizeof(char));
   self->client->message[self->client->message_length] = 0;
    
    for ( int i = 0 ; i < self->client->message_length ; i++ ){
        self->client->message[i] = msg_aux[i];
    }

    //client_set_message(self->client,msg_aux);

    free(msg_aux);
    
    return bytes_received;    
}

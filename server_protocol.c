#include "server_protocol.h"
#include "common_communication_protocol.h"

void server_protocol_init
(server_protocol_t* self, socket_t* socket,server_t* server){
    self->peer = socket;
    self->server = server;
}

void server_protocol_start
(server_protocol_t* self,socket_t* socket,cipher_hill_encryptor_t* e){
    communication_protocol_t comm;
    
    communication_protocol_init(&comm,self->peer);
    
    ssize_t bytes_received;
    bytes_received = 
        _server_protocol_receive_message_from_client(self,&comm);

    while (bytes_received > 0){
        cipher_hill_encryptor_init(e,self->server);
        cipher_hill_encryptor_encrypt(e);

        // DELEGAR ESTO A UNA FUNCION
        free(self->server->message_read);
        self->server->message_read_length = e->message_to_encrypt_length;
             
        self->server->message_read = (unsigned char*)
            calloc(self->server->message_read_length+1,sizeof(char));

        for ( int i = 0 ; i < self->server->message_read_length ; i++ ){
            self->server->message_read[i] = (e->message_to_encrypt[i]);
        }

        cipher_hill_encryptor_uninit(e);
            
        _server_protocol_send_message_to_client(self,&comm);

        bytes_received = 
            _server_protocol_receive_message_from_client(self,&comm);

    communication_protocol_uninit(&comm);
    
    }
}

void server_protocol_uninit
(server_protocol_t* self){
    //cierro socket?=¡¡?
}

void _server_protocol_send_message_to_client
(server_protocol_t* self, communication_protocol_t* comm){  
    communication_protocol_send_message
        (comm, self->server->message_read, self->server->message_read_length);
    free(self->server->message_read);
}

ssize_t _server_protocol_receive_message_from_client
(server_protocol_t* self, communication_protocol_t* comm){
    ssize_t bytes_received = 0;
    self->server->message_read_length = 
        communication_protocol_receive_size(comm);

    unsigned char* msg_aux;
    msg_aux = calloc(self->server->message_read_length+1,sizeof(char));

    bytes_received = 
        communication_protocol_receive_message(comm,self->server->message_read_length,msg_aux);
    
    if ( bytes_received > 0){
        self->server->message_read = calloc
            (self->server->message_read_length+2,sizeof(char));
        self->server->message_read[self->server->message_read_length+1] = 0;
        
        for ( int i = 0 ; i < self->server->message_read_length ; i++ ){
            self->server->message_read[i] = msg_aux[i];
        }
    }

    free(msg_aux);

    return bytes_received;
}

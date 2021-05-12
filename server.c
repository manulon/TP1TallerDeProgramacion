#include "server.h"
#include "server_password.h"
#include "server_cipher_hill_encryptor.h"
#include "server_protocol.h"

void server_init(server_t* self, char* const* argv, password_t* key) {
    self->servicename = argv[1];
    self->key = key;
    self->message_read_length = 0;

    password_map(self->key);
    printf("Servidor inicializado... esperando conexion.. \n");
}

void server_uninit(server_t* self){}

void client_communicate_with_client(server_t* self){
    socket_t socket;
	socket_t peer;
    cipher_hill_encryptor_t encryptor;
    server_protocol_t protocol;

    server_protocol_init(&protocol,&peer,self);

    if ( _server_init_connection(self,&socket,&peer) )
        server_protocol_start(&protocol,&socket,&encryptor);
    
    server_protocol_uninit(&protocol,&socket,&peer);
}

bool _server_init_connection
(server_t* self, socket_t* socket,socket_t* peer){
    bool bind_and_listen_ok = false;

    bind_and_listen_ok =
        socket_bind_and_listen(socket, NULL, self->servicename);
    socket_accept(socket, peer);

    return bind_and_listen_ok;
}

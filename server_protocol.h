#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "common_socket.h"
#include "server.h"
#include "server_cipher_hill_encryptor.h"
#include "common_communication_protocol.h"

typedef struct {
    socket_t* peer;
    server_t* server;
}server_protocol_t;

//Lee los parametros de la linea de comandos para inicializar
//los atributos del cliente.
//Pre: todos los parametros fueron pasados correctamente
//Post: el cliente queda listo para ser usado y enviar mensajes.
void server_protocol_init
(server_protocol_t* self, socket_t* socket, server_t* server);

void server_protocol_start
(server_protocol_t* self,socket_t* socket,cipher_hill_encryptor_t* e);

//Cierra los archivos pertinentes.
void server_protocol_uninit
(server_protocol_t* self);

//Delega responsabilidad de enviar mensajes al servidor
void _server_protocol_send_message_to_client
(server_protocol_t* self, communication_protocol_t* comm);

ssize_t _server_protocol_receive_message_from_client
(server_protocol_t* self, communication_protocol_t* comm);

#endif
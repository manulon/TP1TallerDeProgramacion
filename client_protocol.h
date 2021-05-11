#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "common_socket.h"
#include "client.h"
#include "common_communication_protocol.h"

typedef struct {
    socket_t* socket;
    client_t* client;
}client_protocol_t;

//Lee los parametros de la linea de comandos para inicializar
//los atributos del cliente.
//Pre: todos los parametros fueron pasados correctamente
//Post: el cliente queda listo para ser usado y enviar mensajes.
void client_protocol_init
(client_protocol_t* self, socket_t* socket, client_t* client);

void client_protocol_start(client_protocol_t* self);

//Cierra los archivos pertinentes.
void client_protocol_uninit
(client_protocol_t* self);

//Delega responsabilidad de enviar mensajes al servidor
void _client_protocol_send_message
(client_protocol_t* self, communication_protocol_t* comm);

ssize_t _client_protocol_receive_message
(client_protocol_t* self, communication_protocol_t* comm);

void _reset_client_message(client_protocol_t* self);

void _set_new_message
(client_protocol_t* self, unsigned char* msg_aux);

#endif
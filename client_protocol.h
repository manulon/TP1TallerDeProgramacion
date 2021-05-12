#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include "common_socket.h"
#include "client.h"
#include "common_communication_protocol.h"

typedef struct {
    socket_t* socket;
    client_t* client;
}client_protocol_t;

//Crea el protocolo por parte del cliente, asignando el cliente
//a comunicar y el socket que se encargara de realizar la 
//comunicacion.
void client_protocol_init
(client_protocol_t* self, socket_t* socket, client_t* client);

//Da inicio al protocolo de comunicacion cliente-servidor.
//Crea el protocolo de comunicacion comun que se encargara del
//envio de los mensajes.
void client_protocol_start(client_protocol_t* self);

//Termina el protocolo de comunicacion de parte del cliente.
//Esta clase existe de forma teorica para respetar RAII.
void client_protocol_uninit
(client_protocol_t* self);

//---------------Metodos Privados---------------//

//Delega al protocolo comun el envio del mensaje
void _client_protocol_send_message
(client_protocol_t* self, communication_protocol_t* comm);

//Delega al protocolo comun la recepcion del mensaje.
//Luego delega la asignacion del mensaje recibido al mensaje
//propio del cliente.
ssize_t _client_protocol_receive_message
(client_protocol_t* self, communication_protocol_t* comm);

//Se encarga de liberar la memoria que ocupa el mensaje del
//cliente para poder ser ocupada nuevamente.
void _reset_client_message(client_protocol_t* self);

//Se encarga de asignar el mensaje recibido del servidor al
//mensaje propio del cliente.
void _set_new_message
(client_protocol_t* self, unsigned char* msg_aux);

#endif

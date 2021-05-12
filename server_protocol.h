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

//Se crea el protocolo del servidor
//Pre: Los valores recibidos por parametro son validos.
void server_protocol_init
(server_protocol_t* self, socket_t* socket, server_t* server);

//Se cierra el protocolo del servidor. Se cierran los sockets
//que pertenecen a dicho protocolo.
void server_protocol_uninit
(server_protocol_t* self, socket_t* socket, socket_t* peer);

//Se inicia el protocolo por parte del cliente.
//Todas las acciones de dicho protocolo seran delegadas a otras
//entidades
void server_protocol_start
(server_protocol_t* self,socket_t* socket,cipher_hill_encryptor_t* e);

//----------Metodos Privados---------//

//Delega el envio del mensaje del cliente al protocolo comun.
//Luego, resetea el mensaje recibido para que vuelva a poder ser usado
void _server_protocol_send_message_to_client
(server_protocol_t* self, communication_protocol_t* comm);

//Delega la recepcion del mensaje del cliente al protocolo comun.
//Luego, se encarga de asignar el mensaje recibido al cliente.
ssize_t _server_protocol_receive_message_from_client
(server_protocol_t* self, communication_protocol_t* comm);

//Se encarga de cargarle al cliente el mensaje que fue encriptado
//por el cipher hill encryptor.
void _get_new_message
(server_protocol_t* self, cipher_hill_encryptor_t* e);

//Se encarga de liberar la memoria que ocupa el mensaje leido por el
//servidor para que esta pueda ser ocupada nuevamente para un proximo
//mensaje.
void _server_reset_message
(server_protocol_t* self);

#endif


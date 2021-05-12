#ifndef SERVER_H
#define SERVER_H

#include "server_password.h"
#include "common_plaintext.h"
#include "common_socket.h"

typedef struct {
    const char*  servicename;
    password_t*  key;
    unsigned char* message_read;
    short int message_read_length;
} server_t;

//Inicializa un servidor con los parametros correspondientes.
//Pre: se escriben correctamente los parametros requeridos.
//Post: el servidor esta listo para ser usado y recibir
//mensajes.
void server_init(server_t* self, char* const* argv, password_t* key);

//Se inicia la conexion con el cliente
bool _server_init_connection
(server_t* self, socket_t* socket,socket_t* peer);

//Se cierra al servidor. Esta clase existe de manera simbolica 
//para respetar RAII.
void server_uninit(server_t* self);

//Se crea el protocolo por parte del servidor. 
//Si hay una conexion se le da inicio a este.
void server_communicate_with_client(server_t* self);

#endif

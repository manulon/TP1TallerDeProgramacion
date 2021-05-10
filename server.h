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

bool _server_init_connection
(server_t* self, socket_t* socket,socket_t* peer);

//Se cierra al servidor y asi a los archivos necesarios.
void server_uninit(server_t* self);

//Recibe un mensaje cifrado del cliente y lo encripta
//para luego enviarselo de nuevo al cliente.
//La encriptacion es delegada
void client_communicate_with_client(server_t* self);

#endif

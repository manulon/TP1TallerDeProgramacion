#ifndef SERVER_H
#define SERVER_H

#define MAX_LINE_SIZE 40  
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

void server_uninit(server_t* self);

//Recibe un mensaje cifrado del cliente y lo encripta
//para luego enviarselo de nuevo al cliente
void receive_message_from_client(server_t* self);

//should be private
ssize_t receive_size_from_client(server_t* self, socket_t* peer);
ssize_t receive_line_from_client(server_t* self, socket_t* peer);

void send_encrypted_message_to_client(server_t* self, socket_t* socket);

#endif

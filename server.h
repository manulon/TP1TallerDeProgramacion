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

//Se cierra al servidor y asi a los archivos necesarios.
void server_uninit(server_t* self);

//Recibe un mensaje cifrado del cliente y lo encripta
//para luego enviarselo de nuevo al cliente.
//La encriptacion es delegada
void receive_message_from_client(server_t* self);

//Recibe un buffer de 2 bytes que representa el largo del
//mensaje que luego recibira del cliente.
ssize_t _receive_size_from_client(server_t* self, socket_t* peer);

//Recibe el mensaje a encriptar del cliente.
ssize_t _receive_line_from_client(server_t* self, socket_t* peer);

//Delega el envio de mensajes al cliente.
void send_encrypted_message_to_client(server_t* self, socket_t* socket);

#endif

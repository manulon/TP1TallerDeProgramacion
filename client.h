#ifndef CLIENT_H
#define CLIENT_H

#include "common_socket.h"

typedef struct {
    const char* hostname;
    const char* servicename;
    const char* filename;
    unsigned char* message;
    int message_length;
}client_t;

//Lee los parametros de la linea de comandos para inicializar
//los atributos del cliente.
//Pre: todos los parametros fueron pasados correctamente
//Post: el cliente queda listo para ser usado y enviar mensajes.
void client_init
(client_t* self, char** argv);

void client_uninit
(client_t* self);

void client_send_message_to_server
(client_t* self, socket_t* socket);

void client_receive_encrypted_message_from_server
(client_t* self, socket_t* peer);

ssize_t _client_receive_message
(client_t* self, socket_t* peer);

ssize_t _client_receive_size
(client_t* self, socket_t* peer);

void client_decrypt_message
(client_t* self);

void client_init_connection
(client_t* self,socket_t* socket);

#endif

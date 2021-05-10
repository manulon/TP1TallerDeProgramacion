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

//Cierra los archivos pertinentes.
void client_uninit
(client_t* self);

//Delega responsabilidad de enviar mensajes al servidor
void client_communicate_with_server
(client_t* self,socket_t* socket);

//Desencripta el mensaje recibido desde el servidor
//Pre: Le llega un mensaje bien encriptado.
//Post: El mensaje es desencriptado.
void _client_decrypt_message
(client_t* self);

void _client_print_message
(client_t* self);

//Hace un socket connect para entablecer la conexion con el 
//cliente.
//Post: Se establecio una conexion.
void client_init_connection
(client_t* self,socket_t* socket);

void client_set_message_length(client_t* self, int len);

void client_set_message(client_t* self, unsigned char* msg);

unsigned char* client_get_message(client_t* self);

int client_get_message_length(client_t* self);


#endif

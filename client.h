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

//Inicia un cliente con los valores que recibe de la linea
//de comandos. 
//Pre: Los valores son validos.
void client_init
(client_t* self, char** argv);

//"Desinicializa" a un cliente, este metodo esta de forma 
//simbolica para respetar RAII.
void client_uninit
(client_t* self);

//Inicia la comunicacion con el cliente. De haber leido 
//un mensaje del archivo inicia el protocolo de envio del mismo
// y luego lo desencripta y lo imprime por la salida estandar.
void client_communicate_with_server
(client_t* self,socket_t* socket);

//Inicializa la conexion con el servidor conectando el socket.
void client_init_connection
(client_t* self,socket_t* socket);

//Finaliza la conexion cerrando el socket asociado a la misma.
void client_uninit_connection
(client_t* self,socket_t* socket);

//Asigna como largo del mensaje el parametro recibido.
void client_set_message_length
(client_t* self, int len);

//Asigna como mensaje el mensaje recibido como parametro.
void client_set_message
(client_t* self, unsigned char* msg);

//Devuelve el mensaje.
unsigned char* client_get_message
(client_t* self);

//Devuelve el largo del mensaje.
int client_get_message_length
(client_t* self);

//---------------Metodos Privados------------------//

//Metodo que se encarga de realizar la encriptacion del 
//mensaje recibido.
void _client_decrypt_message
(client_t* self);

//Metodo que se encarga de imprimir el mensaje en su 
//estado final por la entrada estandar.
void _client_print_message
(client_t* self);

#endif

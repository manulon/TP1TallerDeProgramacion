#ifndef COMMON_COMMUNICATION_PROTOCOL_H
#define COMMON_COMMUNICATION_PROTOCOL_H

#include "common_socket.h"

typedef struct{
    socket_t* socket;
}communication_protocol_t;

//Inicia el protocolo de comunicacion entre cliente y servidor.
void communication_protocol_init
(communication_protocol_t* self, socket_t* socket);

//Cierra el protocolo de comunicacion comun. 
//Esta clase esta solo con fines simbolicos para respetar RAII.
void communication_protocol_uninit
(communication_protocol_t* self);

//Delega la recepcion completa del mensaje. 
//Primero envia el size del mensaje y luego el mensaje en si.
ssize_t communication_protocol_send_message
(communication_protocol_t* self, unsigned char* msg, int length);

//Recibe un el size del mensaje que luego se le enviara.
//Post: Devuelve el size del mensaje recibido.
int communication_protocol_receive_size
(communication_protocol_t* self);

//Recibe un mensaje del tamaño length.
ssize_t communication_protocol_receive_message
(communication_protocol_t* self, int length, unsigned char* buffer);

//---------------Metodos Privados-----------------//

//Se encarga de cumplir el protocolo para el envio de un tamaño.
ssize_t _send_size
(communication_protocol_t* self, int size);

//Se encarga de cumplir el protocolo para el envio de un mensaje.
ssize_t _send_message
(communication_protocol_t* self, unsigned char* msg, int size);

//Se encarga de pasar un entero a un array de dos posiciones para 
//que el socket lo pueda entender y poder enviarlo.
void _short_to_char
(short int size,unsigned  char* buffer);

//Se encarga de pasar un array de dos posiciones a un entero para
//que el receptor lo pueda entender y usarlo como tamaño de mensaje.
short int _char_to_short
(unsigned char* buffer);

#endif

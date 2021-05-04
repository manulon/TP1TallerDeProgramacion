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
void client_send_message_to_server
(client_t* self, socket_t* socket);

//Recibe un mensaje del servidor. Metodo privado.
//Post: devuelve la cantidad de bytes recibidos por parte
//del servidor.
ssize_t _client_receive_message
(client_t* self, socket_t* peer);

//Recibe el largo del mensaje que sera recibido del servidor.
//Post: devuelve la cantidad de bytes recibidos por parte
//del servidor.
ssize_t _client_receive_size
(client_t* self, socket_t* peer);

//Desencripta el mensaje recibido desde el servidor
//Pre: Le llega un mensaje bien encriptado.
//Post: El mensaje es desencriptado.
void client_decrypt_message
(client_t* self);

//Hace un socket connect para entablecer la conexion con el 
//cliente.
//Post: Se establecio una conexion.
void client_init_connection
(client_t* self,socket_t* socket);

//Delega envio del mensaje encriptado.
void client_receive_encrypted_message_from_server
(client_t* self,socket_t* peer);

#endif

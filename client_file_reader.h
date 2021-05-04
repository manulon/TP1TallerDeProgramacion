#ifndef CLIENT_FILE_READER_H
#define CLIENT_FILE_READER_H

#define  _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include "server_password.h"
#include "client.h"

typedef struct {
    FILE* fp;
} file_reader_t;

//Abre un archivo
//Pre: recibe un nombre de archivo como parámetro
//Post devuelve 0 si el archivo fue abierto correctamente, 
int file_reader_init(file_reader_t* self, const char* file_name);

//Lee una linea del archivo y lo guarda en memoria.
//Pre: El archivo a leer existe.
//Post: La funcion devuelve 0 en caso de que se haya
//leido una linea y -1 en el que no.
//La linea leida se guarda en client->message y su largo
//en client->message_length
int file_reader_read_chunk(file_reader_t* self, client_t* client);

//Ciera el archivo abierto en init
//Pre: un file reader fue inicializado.
//Post devuelve 0 si el archivo fue cerrado correctamente, 
//-1 en caso de error.
int file_reader_uninit(file_reader_t* self);

//Itera sobre todo el archivo y le envia al servidor el 
//largo y mensaje leido. Luego recibe la respuesta y la 
//imprime en la salida estandar.
//Pre: Ya existe una conexion con el servidor.
//Post: Se ha leido todo el archivo.
void file_reader_iterator
(file_reader_t* self, client_t* client,socket_t* socket);

#endif

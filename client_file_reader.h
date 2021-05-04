#ifndef CLIENT_FILE_READER_H
#define CLIENT_FILE_READER_H

#define  _POSIX_C_SOURCE 200809L
#define  MAX_LINE_SIZE 200
#include <stdio.h>
#include <stdlib.h>
#include "server_password.h"
#include "client.h"

typedef struct {
    FILE* fp;
} file_reader_t;

//CAMBIAR LAS PRE Y POST---------

//Abre un archivo
//Pre: recibe un nombre de archivo como parámetro
//Post devuelve 0 si el archivo fue abierto correctamente, 
//-1 en caso de error.
int file_reader_init(file_reader_t* self, const char* file_name);

int file_reader_read_chunk(file_reader_t* self, client_t* client);

//Ciera el archivo abierto en init
//Pre: un file reader fue inicializado.
//Post devuelve 0 si el archivo fue cerrado correctamente, 
//-1 en caso de error.
int file_reader_uninit(file_reader_t* self);

void file_reader_iterator
(file_reader_t* self, client_t* client,socket_t* socket);

#endif

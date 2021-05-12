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

//Inicializa el file reader.
int file_reader_init(file_reader_t* self, const char* file_name);

//Lee un chunk y se lo asigna al cliente con su largo.
//Post: Devuelve true si se ha leido una linea del archivo.
bool file_reader_read_chunk(file_reader_t* self, client_t* client);

//Cierra el file reader, cerrando el archivo del cual se ha leido
//las lineas. 
//Pre: El archivo fue abierto con anterioridad.
int file_reader_uninit(file_reader_t* self);

#endif

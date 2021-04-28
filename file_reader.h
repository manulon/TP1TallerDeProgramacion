#ifndef FILE_READER_H
#define FILE_READER_H

#define  _POSIX_C_SOURCE 200809L
#define  MAX_LINE_SIZE 40
#include <stdio.h>
#include <stdlib.h>
#include "plaintext.h"
#include "password.h"
#include "cipher_hill_encryptor.h"

typedef struct {
    FILE* fp;
} file_reader_t;

//CAMBIAR LAS PRE Y POST---------

//Abre un archivo
//Pre: recibe un nombre de archivo como parámetro
//Post devuelve 0 si el archivo fue abierto correctamente, 
//-1 en caso de error.
int file_reader_init(file_reader_t* self, const char* file_name);

//Lee el archivo abierto en init.
//Pre: se inicializó un file_reader_t
void file_reader_iterator(file_reader_t* self, 
plaintext_t* plaintext,password_t* password);

void file_reader_read_plaintext_from_file(file_reader_t* self, plaintext_t* plaintext);

//Ciera el archivo abierto en init
//Pre: un file reader fue inicializado.
//Post devuelve 0 si el archivo fue cerrado correctamente, 
//-1 en caso de error.
int file_reader_uninit(file_reader_t* self);

#endif

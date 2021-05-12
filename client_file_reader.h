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

int file_reader_init(file_reader_t* self, const char* file_name);
bool file_reader_read_chunk(file_reader_t* self, client_t* client);
int file_reader_uninit(file_reader_t* self);

#endif

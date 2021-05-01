#include "client_file_reader.h"

#include <stdio.h>
#include <string.h>

int file_reader_init
(file_reader_t* self, const char* file_name) {
    if (file_name == NULL) {
        self->fp = stdin;
    } else {
        self->fp = fopen(file_name, "rb");
    }
    return 0;
}

void file_reader_read_chunk
(file_reader_t* self, client_t* client){
    char* chunk;
    size_t buffer_size = MAX_LINE_SIZE;
    size_t buffer_read = 0;

    chunk = (char *)malloc(MAX_LINE_SIZE * sizeof(char));

    buffer_read = getline(&chunk,&buffer_size,self->fp);

    client->message = (char *)malloc( (buffer_read+1) * sizeof(char));
    
    strncpy(client->message,chunk,buffer_read);
    client->message[buffer_read+1] = '\0';

    client->message_length = (buffer_read+1);

    free(chunk);
}

int file_reader_uninit
(file_reader_t* self) {
    if (self->fp != stdin) {
        if (fclose(self->fp) == EOF) {
            return -1;
        }
    }
    return 0;
}

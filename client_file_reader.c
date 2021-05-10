#include "client_file_reader.h"

#include <stdio.h>
#include <string.h>

int file_reader_init
(file_reader_t* self, const char* file_name) {
    if (strcmp(file_name, "-") == 0){
            self->fp = stdin;
    }else {
        self->fp = fopen(file_name, "rb");
    }
    return 0;
}

bool file_reader_read_chunk
(file_reader_t* self, client_t* client){
    char* chunk = NULL;
    size_t buffer_size = 0;
    size_t buffer_read = 0;

    buffer_read = getline(&chunk,&buffer_size,self->fp);

    if (buffer_read == -1){
        free(chunk);
        return false;
    }
    
    client->message = calloc(buffer_read+1, sizeof(char));
    
    strncpy((char*)client->message,chunk,buffer_read);
    client->message[buffer_read] = 0;
    client->message_length = (buffer_read);
    free(chunk);

    return true;
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
    
#include "client_file_reader.h"

#include <stdio.h>
#include <string.h>

#define MAX_STDIN_SIZE 100


int file_reader_init
(file_reader_t* self, const char* file_name) {
    if (strcmp(file_name, "-") == 0){
            self->fp = stdin;
    }else {
        self->fp = fopen(file_name, "rb");
    }
    return 0;
}

int file_reader_read_chunk
(file_reader_t* self, client_t* client){
    char* chunk;
    size_t buffer_size = MAX_LINE_SIZE;
    size_t buffer_read = 0;

    chunk = ( char *)malloc(MAX_LINE_SIZE * sizeof( char));

    buffer_read = getline(&chunk,&buffer_size,self->fp);

    if (buffer_read == -1) return 1;

    client->message = (unsigned char *)malloc
    ( (buffer_read+1) * sizeof(unsigned char));
    
    strncpy((char*)client->message,chunk,buffer_read);
    client->message[buffer_read+1] = '\0';

    client->message_length = (buffer_read+1);
    free(chunk);

    return 0;
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

void file_reader_iterator
(file_reader_t* self, client_t* client,socket_t* socket){
    int feof = file_reader_read_chunk(self,client);
    while (!feof){
        socket_send_size(socket,(short int)client->message_length);
        socket_send_message(socket,client->message,client->message_length);

        free(client->message); 
        
        client_receive_encrypted_message_from_server(client,socket);
    
        client_decrypt_message(client);

        unsigned char aux[1] = {"\n"};
        client->message[client->message_length] = aux[0];
        fwrite(client->message, sizeof(unsigned char),
         (client->message_length+1), stdout);
        
        free(client->message);

        feof = file_reader_read_chunk(self,client);
    }
}

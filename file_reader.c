#include "file_reader.h"

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

void file_reader_iterator
(file_reader_t* self, plaintext_t* plaintext,password_t* password) {
    plaintext_t final_plaintext;
    cipher_hill_encryptor_t encryptor;

    password_map(password);

    while (!feof(self->fp)){
        file_reader_read_plaintext_from_file(self, plaintext);
        plaintext_init(&final_plaintext,40);
        printf("Lei del archivo: %s",plaintext->line);
        cipher_hill_encryptor_init(&encryptor,
        &final_plaintext, 
        plaintext, password);
        cipher_hill_encryptor_encrypt(&encryptor);
        printf("Mapeo a: \t");
        for (int i=0; i<(plaintext_get_line_length(&final_plaintext)); i++){
            printf("%c",plaintext_get(&final_plaintext,i));
        }
        printf("\n\t----------\n");
        cipher_hill_encryptor_uninit(&encryptor);

        plaintext_uninit(&final_plaintext);
    
    }
}

void file_reader_read_plaintext_from_file
(file_reader_t* self, plaintext_t* plaintext){
    char* buffer;
    size_t buffer_size = MAX_LINE_SIZE;
    size_t buffer_read;

    buffer = (char *)malloc(MAX_LINE_SIZE * sizeof(char));

    buffer_read = getline(&buffer,&buffer_size,self->fp);

    plaintext_set_line(plaintext,buffer,buffer_size);
    plaintext_set_line_length(plaintext,buffer_read);
    free(buffer);
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

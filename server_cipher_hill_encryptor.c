#include "server_cipher_hill_encryptor.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void cipher_hill_encryptor_init
(cipher_hill_encryptor_t* self,server_t* server){
    self->password = server->key;
    
    int length = server->message_read_length;
    self->message_to_encrypt = (char *)malloc( length * sizeof(char) );
    strcpy(self->message_to_encrypt, server->message_read);
}

void cipher_hill_encryptor_encrypt(cipher_hill_encryptor_t* self){
    matrix_t matrix;

    plaintext_t plaintext;

    plaintext_init(&plaintext, sizeof(self->message_to_encrypt));
    plaintext_set_line(&plaintext,self->message_to_encrypt,sizeof(self->message_to_encrypt));

    plaintext_map_and_filter(&plaintext);
 
    matrix_init(&matrix,*(self->password));

    plaintext_fill_with_zero(&plaintext,matrix_get_dimension(&matrix));

    matrix_product(&matrix,&plaintext);
    
    /* no me anda el strcpy
    strncpy(self->message_to_encrypt,plaintext.line);*/

    for( int i=0; i<sizeof(self->message_to_encrypt); i++){
        self->message_to_encrypt[i] = plaintext.line[i];
    }

    free(plaintext.line);
}

void cipher_hill_encryptor_uninit
(cipher_hill_encryptor_t* self){
    free(self->message_to_encrypt);
}

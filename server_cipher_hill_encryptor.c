#include "server_cipher_hill_encryptor.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void cipher_hill_encryptor_init
(cipher_hill_encryptor_t* self,server_t* server){
    self->password = server->key;
    
    self->message_to_encrypt_length = server->message_read_length;
    self->message_to_encrypt = 
        calloc(self->message_to_encrypt_length+2, sizeof(char));

    strncpy((char*)self->message_to_encrypt, 
    (char*)server->message_read,(server->message_read_length));
}

void cipher_hill_encryptor_encrypt(cipher_hill_encryptor_t* self){
    matrix_t matrix;

    plaintext_t plaintext;
    plaintext_init(&plaintext,self->message_to_encrypt_length);
    plaintext_set_line(&plaintext,self->message_to_encrypt
                        ,self->message_to_encrypt_length);

    plaintext_map_and_filter(&plaintext);
    
    matrix_init(&matrix,*(self->password));

    plaintext_fill_with_zero(&plaintext,matrix_get_dimension(&matrix));

    matrix_product(&matrix,&plaintext);
   
    _get_new_message_to_encrypt(self,&plaintext);

    matrix_uninit(&matrix);
    plaintext_uninit(&plaintext); 
}

void cipher_hill_encryptor_uninit
(cipher_hill_encryptor_t* self){
    free(self->message_to_encrypt);
}

void _get_new_message_to_encrypt
(cipher_hill_encryptor_t* self,plaintext_t* plaintext){
    self->message_to_encrypt_length = plaintext->line_length;
        
    free(self->message_to_encrypt);
  
    self->message_to_encrypt = 
        calloc(self->message_to_encrypt_length+2, sizeof(char));

    for ( int i = 0 ; i < self->message_to_encrypt_length ; i++ ){
        self->message_to_encrypt[i] = plaintext->line[i];
    }
        
    self->message_to_encrypt[self->message_to_encrypt_length+1] = '\0';
    
}

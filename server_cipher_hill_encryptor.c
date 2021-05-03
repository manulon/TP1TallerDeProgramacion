#include "server_cipher_hill_encryptor.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void cipher_hill_encryptor_init
(cipher_hill_encryptor_t* self,server_t* server){
    self->password = server->key;
    
    self->message_to_encrypt_length = server->message_read_length;
    self->message_to_encrypt = (unsigned char *)
    malloc( self->message_to_encrypt_length * sizeof(unsigned char) );
    strncpy((char*)self->message_to_encrypt, 
    (char*)server->message_read,(server->message_read_length+1));
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
    
    /* no me anda el strcpy
    strncpy(self->message_to_encrypt,plaintext.line);*/

    self->message_to_encrypt_length = plaintext.line_length;
    
    free(self->message_to_encrypt);
    self->message_to_encrypt = (unsigned char *)malloc
    ( (self->message_to_encrypt_length+1) * sizeof(unsigned char) );

    for ( int i = 0 ; i < self->message_to_encrypt_length ; i++ ){
        self->message_to_encrypt[i] = plaintext.line[i];
    }
    
    self->message_to_encrypt[self->message_to_encrypt_length+1] = '\0';


    free(plaintext.line);
    matrix_uninit(&matrix);
    //deberia hacer free
    plaintext_uninit(&plaintext); 
}

void cipher_hill_encryptor_uninit
(cipher_hill_encryptor_t* self){
    free(self->message_to_encrypt);
}

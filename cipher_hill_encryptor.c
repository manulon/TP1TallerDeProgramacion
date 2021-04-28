#include "cipher_hill_encryptor.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void cipher_hill_encryptor_init
(cipher_hill_encryptor_t* self,plaintext_t* final_plaintext, 
plaintext_t* plaintext, password_t* password){
    self->final_plaintext = final_plaintext;
    self->plaintext = plaintext;
    self->password = password;
}

void cipher_hill_encryptor_encrypt(cipher_hill_encryptor_t* self){
    matrix_t matrix;
    plaintext_map_and_filter(self->plaintext);
    matrix_init(&matrix,*(self->password));
    plaintext_fill_with_zero(self->plaintext,matrix_get_dimension(&matrix));
    matrix_product(&matrix,self->final_plaintext,*(self->plaintext));
    plaintext_unmap(self->final_plaintext);

    matrix_uninit(&matrix);
}

void cipher_hill_encryptor_uninit
(cipher_hill_encryptor_t* self){
    //no hace nada DISCORDDDD
}

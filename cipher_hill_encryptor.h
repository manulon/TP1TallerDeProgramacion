#ifndef CIPHER_HILL_ENCRYPTOR_H
#define CIPHER_HILL_ENCRYPTOR_H

#include <stdio.h>
#include <stdlib.h>
#include "plaintext.h"
#include "matrix.h"

typedef struct {
    password_t* password;
    plaintext_t* plaintext;
    plaintext_t* final_plaintext;
} cipher_hill_encryptor_t;

void cipher_hill_encryptor_init(cipher_hill_encryptor_t* self,
plaintext_t* final_plaintext, plaintext_t* plaintext, 
password_t* password);

void cipher_hill_encryptor_uninit(cipher_hill_encryptor_t* self);

void cipher_hill_encryptor_encrypt(cipher_hill_encryptor_t* self);

#endif

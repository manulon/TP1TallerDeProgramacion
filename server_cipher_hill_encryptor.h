#ifndef SERVER_CIPHER_HILL_ENCRYPTOR_H
#define SERVER_CIPHER_HILL_ENCRYPTOR_H

#include <stdio.h>
#include <stdlib.h>
#include "common_plaintext.h"
#include "server_matrix.h"
#include "server.h"

typedef struct {
    password_t* password;
    unsigned char* message_to_encrypt;
    int   message_to_encrypt_length;
    plaintext_t* final_plaintext;
} cipher_hill_encryptor_t;

void cipher_hill_encryptor_init
(cipher_hill_encryptor_t* self,server_t* server);

void cipher_hill_encryptor_uninit(cipher_hill_encryptor_t* self);

void cipher_hill_encryptor_encrypt(cipher_hill_encryptor_t* self);

#endif

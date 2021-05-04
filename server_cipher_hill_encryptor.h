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

//Inicializa el encriptador.
void cipher_hill_encryptor_init
(cipher_hill_encryptor_t* self,server_t* server);

//Finaliza al encriptador. Eliminando la memoria que ocupa 
//la linea a encriptar
void cipher_hill_encryptor_uninit(cipher_hill_encryptor_t* self);

//Recibe un mensje a encriptar y lo encripta.
//Post: El mensaje encriptado se guarda en el atributo
//message_to_encrypt.
void cipher_hill_encryptor_encrypt(cipher_hill_encryptor_t* self);

#endif

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
//Pre: Todos los parametros recibidos son validos.
void cipher_hill_encryptor_init
(cipher_hill_encryptor_t* self,server_t* server);

//Cierra el encriptador. Se libera la memoria del mensaje a encriptar
//para que pueda ser usado nuevamente.
void cipher_hill_encryptor_uninit(cipher_hill_encryptor_t* self);

//Realiza la encriptacion. Delega todos los pasos de esta.
void cipher_hill_encryptor_encrypt(cipher_hill_encryptor_t* self);

//------------Metodos Privados-------------//

//Se encarga de asignarle al mensaje encriptado lo resultante de la 
//encriptacion. 
void _get_new_message_to_encrypt
(cipher_hill_encryptor_t* self,plaintext_t* plaintext);

#endif

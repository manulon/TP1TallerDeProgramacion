#ifndef SERVER_PASSWORD_H
#define SERVER_PASSWORD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* line;                  
    int line_length;
} password_t;

//Inicializa la contraseña con los valores recibidos por parametro.
void  password_init(password_t* self, const char* argv);

//Libera la memoria que ocupa la contraseña
void  password_uninit(password_t* self);

//Mapea la contraseña.
void  password_map(password_t* self);

//Post: Devuelve el largo de la linea
int   password_get_line_length(password_t* self);

//Post: Devuelve un caracter ubicado en la posicion i de la linea.
unsigned char  password_get(password_t* self, int i);

#endif

#ifndef SERVER_PASSWORD_H
#define SERVER_PASSWORD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* line;                  //CONSTANTE
    int line_length;
} password_t;

void  password_init(password_t* self, const char* argv);
void  password_uninit(password_t* self);
void  password_map(password_t* self);
int   password_get_line_length(password_t* self);
unsigned char  password_get(password_t* self, int i);

#endif

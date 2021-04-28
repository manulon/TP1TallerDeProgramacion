#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char line[16];                  //CONSTANTE
    int line_length;
} password_t;

void password_init(password_t* self, const char* argv);
void password_uninit(password_t* self);
void password_map(password_t* self);
void password_calculate_size(password_t* self);
int  password_get_line_length(password_t* self);
char password_get(password_t* self, int i);


#endif

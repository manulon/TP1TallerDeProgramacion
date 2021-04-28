#include "password.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void password_init
(password_t* self, const char* argv){
    self->line_length = 16;
    strncpy(self->line,argv,self->line_length);
    password_calculate_size(self);
}

void password_uninit
(password_t* self){
    // no hace nada, es una formalidad COMO LO DICE EN DISCORD !
}

void password_map
(password_t* self){ 
    for ( int i=0 ; i<self->line_length ; i++ ){ 
        self->line[i] -= 65;
    }
}

void password_calculate_size
(password_t *self){
    int aux_size = 0;
    for (int i=0 ; i<(self->line_length) ; i++){
        if ( (self->line[i] > 64) & (self->line[i] < 91) ){
            aux_size +=1;
        }
    }
    self->line_length = aux_size;
}

int  password_get_line_length(password_t* self){
    return self->line_length;
}

char password_get(password_t* self, int i){
    return self->line[i];
}
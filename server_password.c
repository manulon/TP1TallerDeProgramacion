#include "server_password.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void password_init
(password_t* self, const char* argv){
    self->line_length = 0;

    self->line = calloc(strlen(argv)+1,sizeof(char));

    memcpy((char*)self->line,argv,strlen(argv));
    self->line[strlen(argv)] = 0;

    self->line_length = strlen((char*)self->line);
}

void password_uninit
(password_t* self){
    free(self->line);
}

void password_map
(password_t* self){ 
    for ( int i=0 ; i<self->line_length ; i++ ){ 
        self->line[i] -= 65;
    }
}

int  password_get_line_length(password_t* self){
    return self->line_length;
}

unsigned char password_get(password_t* self, int i){
    return self->line[i];
}

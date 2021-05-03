#include "common_plaintext.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void plaintext_map
(plaintext_t* self){   
    for ( int i=0 ; i<self->line_length ; i++ ){ 
        self->line[i] -= 65;
    }
}

void plaintext_filter
(plaintext_t* self){
    unsigned char aux[self->line_length];
    int aux_length = 0;

    for ( int i=0 ; i<(self->line_length) ; i++ ){
        if ( (self->line[i] > 64) & (self->line[i] < 91) ){
            aux[aux_length] = self->line[i];
            aux_length++;
        }
    }
    
    //pongo el /0 al final.
    strncpy((char*)self->line,(char*)aux,aux_length);
    self->line[aux_length+1] = '\0';                            

    //completo con ceros
    for (int j = (aux_length+2); j < (self->line_length); j++){  
        self->line[j] = 0;
    }
    self->line_length = aux_length;
}

void plaintext_init
(plaintext_t* self, int length){
    self->line_length = length;
    self->line = (unsigned char *)malloc( length * sizeof(unsigned char) );
}

void plaintext_uninit
(plaintext_t* self){
    //NO HACE NADA DISCORDDDDDDDD
}

void plaintext_fill_with_zero
(plaintext_t* self,int dimension){
    if ( self->line_length != 0 ){   
        if ( (self->line_length % dimension)  !=0 ){
            int rest = (self->line_length % dimension);
            int spaces_to_fill = (self->line_length + rest);
            while ( self->line_length < spaces_to_fill ){
                self->line[self->line_length] = 0; 
                self->line_length++;
            }
        }else if ( (self->line_length)==1 ){
            int spaces_to_fill = dimension - 1;
            while ( self->line_length <= (spaces_to_fill) ){
                self->line[self->line_length] = 0; 
                self->line_length++;
            }
        }
    }
}

void plaintext_map_and_filter
(plaintext_t* self){
    plaintext_filter(self);
    if ( self->line_length != 0 ){
        plaintext_map(self);
    }
}

int  plaintext_get_line_length(plaintext_t* self){
    return self->line_length;
}

unsigned char plaintext_get(plaintext_t* self, int i){
    return self->line[i];
}

void plaintext_set_line(plaintext_t* self, unsigned char* buf, size_t length){
    strncpy((char*)self->line,(char*)buf,length);
}

void plaintext_set(plaintext_t* self, int i, unsigned char c){
    self->line[i] = c;
}

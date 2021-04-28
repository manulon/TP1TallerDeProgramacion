#include "file_reader.h"

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
    plaintext_t aux;
    aux.line_length = 0;

    for ( int i=0 ; i<(self->line_length) ; i++ ){
        if ( (self->line[i] > 64) & (self->line[i] < 91) ){
            aux.line[aux.line_length] = self->line[i];
            aux.line_length++;
        }
    }

    strncpy(self->line,aux.line,aux.line_length);
    self->line_length = aux.line_length;
}

void plaintext_init
(plaintext_t* self, int length){
    self->line_length = length;
}

void plaintext_uninit
(plaintext_t* self){
    //NO HACE NADA DISCORDDDDDDDD
}

void plaintext_unmap
(plaintext_t* self){
    for ( int i=0 ; i<self->line_length ; i++ ){ 
        self->line[i] = (self->line[i]) % 26 + 65;
    }
}

void plaintext_fill_with_zero
(plaintext_t* self,int dimension){
    if ( self->line_length != 0 ){
        if ( ((((dimension*dimension) % self->line_length))!= 0) ){
            int spaces_to_fill = (self->line_length + 
            ((dimension*dimension) % self->line_length));
            while ( self->line_length < (spaces_to_fill) ){
                self->line[self->line_length] = 0; 
                self->line_length++;
            }
        }else if( (self->line_length)==1 ){
            int spaces_to_fill = 
            (dimension*dimension) - self->line_length;
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

char plaintext_get(plaintext_t* self, int i){
    return self->line[i];
}

void plaintext_set_line(plaintext_t* self, char* buf, size_t length){
    strncpy(self->line,buf,length);
}

void plaintext_set_line_length(plaintext_t* self, int length){
    self->line_length = length;
}

void plaintext_set(plaintext_t* self, int i, char c){
    self->line[i] = c;
}

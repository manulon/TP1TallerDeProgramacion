#ifndef COMMON_PLAINTEXT_H
#define COMMON_PLAINTEXT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char* line;                  //CONSTANTE
    int line_length;
    short int size;
} plaintext_t;

void  plaintext_map(plaintext_t* self);
void  plaintext_filter(plaintext_t* self);
void  plaintext_map_and_filter(plaintext_t *self);
void  plaintext_read_password(plaintext_t* self,const char* argv);
void  plaintext_init(plaintext_t* self, int length);
void  plaintext_uninit(plaintext_t* self);
void  plaintext_fill_with_zero(plaintext_t* self,int dimension);
int   plaintext_get_line_length(plaintext_t* self);
unsigned char  plaintext_get(plaintext_t* self, int i);
void  plaintext_set_line(plaintext_t* self, unsigned char* buf, size_t length);
void  plaintext_set(plaintext_t* self, int i, unsigned char c);


#endif

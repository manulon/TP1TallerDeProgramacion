#ifndef PLAINTEXT_H
#define PLAINTEXT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char line[40];                  //CONSTANTE
    int line_length;
} plaintext_t;

void plaintext_map(plaintext_t* self);
void plaintext_unmap(plaintext_t* self);
void plaintext_filter(plaintext_t* self);
void plaintext_map_and_filter(plaintext_t *self);
void plaintext_read_password(plaintext_t* self,const char* argv);
void plaintext_init(plaintext_t* self, int length);
void plaintext_uninit(plaintext_t* self);
void plaintext_fill_with_zero(plaintext_t* self,int dimension);
int  plaintext_get_line_length(plaintext_t* self);
char plaintext_get(plaintext_t* self, int i);
void plaintext_set_line(plaintext_t* self, char* buf, size_t length);
void plaintext_set_line_length(plaintext_t* self, int length);
void plaintext_set(plaintext_t* self, int i, char c);

#endif

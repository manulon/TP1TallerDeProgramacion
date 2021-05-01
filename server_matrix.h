#ifndef SERVER_MATRIX_H
#define SERVER_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "common_plaintext.h"
#include "server_password.h"

typedef struct {
    int square_matrix[4][4];           //CONSTANTE MAX MATRIX SIZE
    int dimension;
    int initial_row_length;
} matrix_t;

void matrix_init(matrix_t* self,password_t password);
void matrix_uninit(matrix_t* self);
void matrix_product(matrix_t* self,plaintext_t* plaintext);
int  matrix_get_dimension(matrix_t *self);


#endif

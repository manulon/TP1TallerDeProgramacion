#ifndef SERVER_MATRIX_H
#define SERVER_MATRIX_H

#define MAX_SIZE 4

#include <stdio.h>
#include <stdlib.h>
#include "server_plaintext.h"
#include "server_password.h"

typedef struct {
    int square_matrix[MAX_SIZE][MAX_SIZE];           
    int dimension;
    int initial_row_length;
} matrix_t;

//Inicializa una matriz, seteandole a sus parametros
//los valores necesarios.
void matrix_init(matrix_t* self,password_t password);

//"un-inicializa" una matriz. Esta funcion no hace nada
//pero esta de manera simbolica para respetar RAII.
void matrix_uninit(matrix_t* self);

//Realiza el producto matricial.
//Pre: Recibe un plaintext valido para realizar la operacion
void matrix_product(matrix_t* self,plaintext_t* plaintext);

//Devuelve la dimension de la matriz.
int  matrix_get_dimension(matrix_t *self);


#endif

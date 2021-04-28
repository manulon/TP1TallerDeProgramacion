#include "matrix.h"

#include <math.h>
#include <stdio.h>



void matrix_init
(matrix_t* self, password_t password){
    self->initial_row_length = password_get_line_length(&password);
    self->dimension = sqrt(self->initial_row_length);

    int aux = (self->initial_row_length / (int)(self->dimension));
    int l = 0;
    for ( int i = 0 ; i<aux ; i++ ){
        int k = 0;
        for ( int j=0 ; j<(int)(self->dimension) ; j++ ){
            self->square_matrix[i][k] = password_get(&password,l);
            k++;
            l++;
        }
    }
}

void matrix_uninit
(matrix_t* self){
    //NO HACE NADA COMO SIEMRPE, DISCORD !!!!
}

void matrix_product
(matrix_t* self, plaintext_t* final_plaintext,plaintext_t plaintext){ 
    int aux = 0;
    int suma = 0;

    while ( (aux < (plaintext_get_line_length(&plaintext))) 
          & (plaintext_get_line_length(&plaintext) != 0) ){
        for ( int i=0 ; i < self->dimension ; i++ ){
            plaintext_set(final_plaintext,i+aux,0);
            for ( int j=0 ; j < self->dimension ; j++ ){            
                suma = (plaintext_get(final_plaintext,i+aux)) +
                (self->square_matrix[i][j] * plaintext_get(&plaintext,j+aux));
                plaintext_set(final_plaintext,i+aux,suma);
            }
        }
        aux += self->dimension;
    }
    plaintext_set_line_length(final_plaintext,aux);
}

int  matrix_get_dimension(matrix_t *self){
    return self->dimension;
}

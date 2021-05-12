#include "server_matrix.h"
#include "server_password.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

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
(matrix_t* self){}

void matrix_product
(matrix_t* self,plaintext_t* plaintext){ 
    int aux = 0;
    plaintext_t final_plaintext;

    plaintext_init(&final_plaintext, plaintext_get_line_length(plaintext));
    
    while ( (aux < (plaintext_get_line_length(plaintext))) 
          & (plaintext_get_line_length(plaintext) != 0) ){
        for ( int i=0 ; i < self->dimension ; i++ ){
            plaintext_set(&final_plaintext,i+aux,0);
            for ( int j=0 ; j < self->dimension ; j++ ){
                int matrix = self->square_matrix[i][j];
                int vector = plaintext_get(plaintext,j+aux);
                //int vector = plaintext->line[j+aux];

                uint16_t result = final_plaintext.line[i+aux] + 
                                    (vector * matrix);

                /*uint16_t result = final_plaintext.line[i+aux] +
                (self->square_matrix[i][j] * plaintext_get(plaintext,j+aux));
                */
               
                final_plaintext.line[i+aux] = (unsigned char)(result % 26 );
            }
        }
        aux += self->dimension;
    }

    for ( int i=0 ; i < plaintext_get_line_length(plaintext) ; i++ ){
        plaintext_set(plaintext,i,plaintext_get(&final_plaintext,i));
    }
    plaintext_uninit(&final_plaintext);
}

int  matrix_get_dimension(matrix_t *self){
    return self->dimension;
}

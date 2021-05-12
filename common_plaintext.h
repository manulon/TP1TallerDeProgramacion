#ifndef COMMON_PLAINTEXT_H
#define COMMON_PLAINTEXT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char* line;                 
    int line_length;
    } plaintext_t;

//Delega el mapeo y filtrado del plaintext a metodos privados.
void  plaintext_map_and_filter(plaintext_t *self);

//Inicializa un plaintext con los valores recibidos por 
//parametro.
//Pre: La longitud es un entero mayor a cero.
void  plaintext_init(plaintext_t* self, int length);

//Libera la memoria que ocupa la linea del plaintext.
//Pre: Hay un plaintext creado previamente.
void  plaintext_uninit(plaintext_t* self);

//Se encarga de agregar ceros segun sea necesario para realizar
//el producto matricial de la encriptacion.
void  plaintext_fill_with_zero(plaintext_t* self,int dimension);

//Devuelve el largo del la linea del plaintext
int   plaintext_get_line_length(plaintext_t* self);

//Devuelve el caracter que esta ubicado en la posicion que se 
//especifica como parametro.
//Pre: La posicion recibida como parametro es valida.
unsigned char  plaintext_get(plaintext_t* self, int i);

//Setea la nueva linea del plaintext en base a un buffer que se
//recibe como parametro.
//Pre: El length recibido es valido.
void  plaintext_set_line(plaintext_t* self, unsigned char* buf, size_t length);

//Setea el un caracter en una posicion especifica, ambos son 
//especificados en el parametro de la funcion
//Pre: El caracter y la posicion son validos.
void  plaintext_set(plaintext_t* self, int i, unsigned char c);

//-------------Metodos Privados----------------//

//Mapea un plaintext.
void  _plaintext_map(plaintext_t* self);

//Filtra un plaintext.
void  _plaintext_filter(plaintext_t* self);


#endif

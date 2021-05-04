#ifndef COMMON_PLAINTEXT_H
#define COMMON_PLAINTEXT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char* line;                 
    int line_length;
    } plaintext_t;

//Mapea la linea de un plaintext. Metodo privado
//Pre: Llega un plaintext valido para mapear.
//Post: El plaintext es mapeado 
void  _plaintext_map(plaintext_t* self);

//Recibe un plaintext y filtra los caracteres que
//no son necesarios para la encriptacion. Metodo privado
//Pre: Llega un plaintext valido para filtrar.
//Post: El plaintext es filtrado.
void  _plaintext_filter(plaintext_t* self);

//Delega comportamiento del filtrado y mapeo.
void  plaintext_map_and_filter(plaintext_t *self);

//Pre: El largo recibido del plaintext es mayor a cero.
//Post: Inicializa un plaintext.
void  plaintext_init(plaintext_t* self, int length);

//Se libera la memoria que ocupa la linea del plaintext.
void  plaintext_uninit(plaintext_t* self);

//Completa con 0's la linea del plaintext para que sea 
//compatible el producto con la matriz.
//Pre: La dimension de la matriz es un numero entero y
// perteneciente a {2,3,4}
//Post: La linea del plaintext ha sido rellenada.
void  plaintext_fill_with_zero(plaintext_t* self,int dimension);

//Devuelve el largo que ocupa la linea del plaintext.
int   plaintext_get_line_length(plaintext_t* self);

//Pre: La posicion de la linea recibida como parametro es
//valida
//Post: Se devuelve el caracter ubicado en la linea pedida.
unsigned char  plaintext_get(plaintext_t* self, int i);

//Guarda en la linea del plaintext lo recibido por el 
//parametro buf
//Pre: Lo que se quiere guardar en el plaintext puede entrar
//en el.
void  plaintext_set_line(plaintext_t* self, unsigned char* buf, size_t length);

//Pre: La posicion recibida como parametro es valida.
//Post: Guarda en la posicion i de la linea del plaintext
//el caracter recibido como parametro.
void  plaintext_set(plaintext_t* self, int i, unsigned char c);


#endif

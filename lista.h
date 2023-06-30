#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//ELEM1_MAYOR_QUE_ELEM2 = 0
//ELEM1_IGUAL_QUE_ELEM2 = 1
//ELEM1_MENOR_QUE_ELEM2 = 2
typedef enum {
ELEM1_MAYOR_QUE_ELEM2,
ELEM1_IGUAL_QUE_ELEM2,
ELEM1_MENOR_QUE_ELEM2
} comparacion_resultado_t;



struct elemento {
int a;   //cantidad de apariciones de la palabra
char *b; //la palabra
};

typedef struct elemento elemento_t;

typedef comparacion_resultado_t (funcion_comparacion_t) (elemento_t *elem1,elemento_t *elem2);

typedef struct celda celda_t;


struct lista {
celda_t *primera; //puntero a la primera celda de la lista
int cantidad; // cantidad de elementos de la lista
};

typedef struct lista lista_t;

//Crea una lista vacıa y la devuelve.(SE ABRE UN MALLOC)
lista_t* lista_crear();

//Devuelve un puntero al elemento que ocupa la posicion pos de la lista
elemento_t* lista_elemento(lista_t *l, unsigned int pos);

//Devuelve un "boolean" (0 o 1) dependiendo de si la lista esta vacia o no
int lista_vacia(lista_t lista);

// Inserta el elemento elem en la posicion pos de la lista.
int lista_insertar(lista_t *l, elemento_t *elemen, unsigned int pos);

//Elimina el elemento de la posicion pos de la lista.
elemento_t* lista_eliminar(lista_t *l, unsigned int pos);

//Devuelve la cantidad de elementos de la lista l.
unsigned int lista_cantidad(lista_t *l);

//intercambia los elementos de dos posiciones de la lista.
void lista_intercambiar(lista_t *l,int pos1, int pos2);

//Dada la lista l y la funcion comparar ordena la lista de acuerdo al criterio de dicha funcion.
int lista_ordenar(lista_t *l, funcion_comparacion_t comparar);

//funcion comparador utilizada en lista_ordenar
comparacion_resultado_t funcion_comparacion_ejemplo(elemento_t *elem1, elemento_t *elem2);

#endif // LISTA_H_INCLUDED

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
typedef enum {
ELEM1_MAYOR_QUE_ELEM2,
ELEM1_IGUAL_QUE_ELEM2,
ELEM1_MENOR_QUE_ELEM2
} comparacion_resultado_t;

struct elemento {
int a;
char *b;
};

typedef struct elemento elemento_t;

typedef comparacion_resultado_t (funcion_comparacion_t) (elemento_t *elem1,elemento_t *elem2);

typedef struct celda celda_t;

struct lista {
celda_t *primera; //puntero a la primera celda de la lista
int cantidad; // cantidad de elementos de la lista
};

typedef struct lista lista_t;



#endif // LISTA_H_INCLUDED

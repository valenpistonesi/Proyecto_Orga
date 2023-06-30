#ifndef MULTISET_H_INCLUDED
#define MULTISET_H_INCLUDED

struct trie;
typedef struct trie multiset_t;

//Crea un multiset vacio de palabras y lo devuelve.
multiset_t* multiset_crear();

//Inserta la palabra s al multiset m.
void multiset_insertar(multiset_t *m, char *s);

//Devuelve la cantidad de repeticiones de la palabra s en el multiset m.
int multiset_cantidad(multiset_t *m, char *s);

//funcion auxiliar que multiset_elementos utiliza para insertar las palabras a la lista
lista_t* insertarPreOrdenAux(multiset_t *arbol, lista_t *lista, char *palabra, int nivel);

//devuelve una lista con las palabras dentro del multiset dado como parametro
lista_t multiset_elementos(multiset_t *m, comparacion_resultado_t (*f)(elemento_t*, elemento_t*));

//funcion que recorre el multiset
void multiset_recorredor_m(multiset_t *m);

/*Elimina el multiset m liberando el espacio
de memoria reservado. Luego de la invocacion m debe valer NULL.*/
void multiset_eliminar(multiset_t **m);

#endif // MULTISET_H_INCLUDED

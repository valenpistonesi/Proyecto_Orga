#include "multiset.h"

struct trie{
int cantidad; // Cantidad de veces que aparece esa palabra en el multiset
struct trie *siguiente[26];
};

// A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7,I=8,J=9,K=10,L=11,M=12,N=13,
//O=14,P=15,Q=16,R=17,S=18,T=19,U=20,V=21,W=22,X=23,Y=24,Z=25.

//Crea un multiset vacio de palabras y lo devuelve.
multiset_t* multiset_crear(){
    multiset_t *devolver;
    devolver = malloc(sizeof(multiset_t));
    devolver ->cantidad = 0;
    for (int i = 0; i< 26; i++){
        devolver -> siguiente[i] = NULL;
    }

    return devolver;
}


//Inserta la palabra s al multiset m.
void multiset_insertar(multiset_t *m, char *s){
    multiset_t *m_actual = m;
    for(int i = 0; s[i] != '\0'; i++){
        int letra_actual = s[i]- 97; //ascii, entiendo que se debe hacer una conversion directa
        if (m_actual -> siguiente[letra_actual] == NULL){
            m_actual -> siguiente[letra_actual] = multiset_crear();
            m_actual -> siguiente[letra_actual] -> cantidad = 1;
            m_actual = m_actual-> siguiente[letra_actual];
        }
        else{
            (m_actual-> siguiente[letra_actual])-> cantidad = (m_actual-> siguiente[letra_actual])->cantidad + 1;
             m_actual = m_actual-> siguiente[letra_actual];
            }
    }
}

//Devuelve la cantidad de repeticiones de la palabra s en el multiset m.
int multiset_cantidad(multiset_t *m, char *s){
    int cantidad= 0;
    multiset_t *actual = malloc(sizeof(multiset_t));
    actual =m;
    if(s[0] !='\0' && actual -> siguiente[s[0] -97]!= NULL){
        cantidad = (actual -> siguiente[s[0]-97]) -> cantidad;
    }

    for(int i = 0; s[i] != '\0' && cantidad; i++){
        if(actual -> siguiente[s[i] -97]!= NULL){
            if( ((actual -> siguiente[s[i]-97]) -> cantidad) < cantidad )
               cantidad = (actual -> siguiente[s[i]-97]) -> cantidad;
        }
         else cantidad = 0;
    }

    return cantidad;
}

//funcion auxiliar que multiset_elementos utiliza para insertar las palabras a la lista
lista_t* recorredor_me(multiset_t *m, lista_t *l, char *p, int n){
    elemento_t* elemAux;
    elemAux = malloc(sizeof(elemento_t));
    elemAux -> b = malloc(sizeof(char)*256);

    if(m -> cantidad > 0){
        p [n] = '\0';
        elemAux -> a = m-> cantidad;
        elemAux -> b = strdup(p);
        lista_insertar (l, elemAux, lista_cantidad(l));
    }

    for (int pos = 0; pos < 26; pos++){
        if(m -> siguiente[pos] != NULL){
            p [n]= 97 + pos;
            recorredor_me(m ->siguiente [pos], l,p, n +1);
        }
    }

    return l;
}

//devuelve una lista con las palabras dentro del multiset dado como parametro
lista_t multiset_elementos(multiset_t *m, comparacion_resultado_t (*f)(elemento_t*, elemento_t*)){
    lista_t *l = lista_crear();
    char *palabra = malloc(sizeof(char)*256);
    l = recorredor_me(m, l, palabra, 0);

    return *l;
}

//funcion que recorre el multiset
void multiset_recorredor_m(multiset_t *m){
    for (int i = 0; i< (sizeof(m -> siguiente) / sizeof(m-> siguiente[0])); i++){
        multiset_recorredor_m(m->siguiente[i]);}
    free(m);
}

/*Elimina el multiset m liberando el espacio
de memoria reservado. Luego de la invocacion m debe valer NULL.*/
void multiset_eliminar(multiset_t **m){
    multiset_recorredor_m(*m);
    free(m);
}



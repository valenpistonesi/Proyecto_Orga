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
    return devolver;}


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
            m_actual = m_actual-> siguiente[letra_actual];}}
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
               cantidad = (actual -> siguiente[s[i]-97]) -> cantidad;}
         else cantidad = 0;}
    return cantidad;}

lista_t* insertarPreOrdenAux(multiset_t *arbol, lista_t *lista, char *palabra, int nivel){
    elemento_t* elemAux;
    elemAux = malloc(sizeof(elemento_t));
    elemAux -> b = malloc(sizeof(char)*256);

    if(arbol -> cantidad>0 ){
        palabra [nivel] = '\0';
        elemAux -> a = arbol-> cantidad;
        elemAux -> b = strdup(palabra);
        lista_insertar (lista, elemAux, lista_cantidad(lista));
        /*printf("celda numero");
        printf("%i", nivel);
        printf("\n");
        printf("elem: \n");
        printf("a: ");
        printf("%d", lista_elemento(lista,lista_cantidad(lista)-1)->a);
        printf("  ");
        printf("b: ");
        //printf(celda_nueva->elem->b);
        printf(lista_elemento(lista,lista_cantidad(lista)-1)->b);*/
    }
    for (int pos = 0; pos < 26; pos++){
        if(arbol -> siguiente[pos] != NULL){
            palabra [nivel]= 97 + pos;
            insertarPreOrdenAux(arbol ->siguiente [pos], lista,palabra, nivel +1);
            /*printf("celda numero ");
            printf("%i", nivel);
            printf("\n");
            printf("elem: \n");
            printf("a: ");
            printf("%i", lista_elemento(lista,nivel)->a);
            printf("  ");
            printf("b: ");
            //printf(celda_nueva->elem->b);
            printf(lista_elemento(lista,nivel)->b);*/
        }
    }

    return lista;
}

lista_t multiset_elementos(multiset_t *m, comparacion_resultado_t (*f)(elemento_t*, elemento_t*)){
    lista_t *l = lista_crear();
    char *palabra = malloc(sizeof(char)*256);
    l = insertarPreOrdenAux(m, l, palabra, 0);

    printf("multiset elementos\n");
    /*for (int i=0; i<lista_cantidad(l); i++)
    {
        printf("%s\n", lista_elemento(l, i)->b);
    }
    printf("multiset elementos\n");*/

    return *l;
}
//en base a la funcion insertada generar una funcion compatible con lista_ordenar

void multiset_recorredor_m(multiset_t *m){
    for (int i = 0; i< (sizeof(m -> siguiente) / sizeof(m-> siguiente[0])); i++){
        multiset_recorredor_m(m->siguiente[i]);}
    free(m);
}

//Elimina el multiset m liberando el espacio
//de memoria reservado. Luego de la invocaci´on m debe valer NULL.
void multiset_eliminar(multiset_t **m){
    multiset_recorredor_m(*m);
    free(m);

}



#include "lista.h"

struct celda {
elemento_t *elem;
struct celda *siguiente;
};

//implementacion


//Crea una lista vacıa y la devuelve.(SE ABRE UN MALLOC)
lista_t* lista_crear(){
    lista_t *nueva_lista;
    nueva_lista = malloc(sizeof(lista_t));
    nueva_lista -> cantidad =0;
    nueva_lista -> primera = NULL;
    return nueva_lista;
}

//Devuelve un puntero al elemento que ocupa la posicion pos de la lista
elemento_t* lista_elemento(lista_t *l, unsigned int pos){
    if(l->cantidad > pos){
        celda_t *celda_aux;
        celda_aux = l-> primera;
        for(int i = 0; i < pos; i++){
            celda_aux = celda_aux -> siguiente;
        }
        return celda_aux -> elem;
    }
    else return NULL;
    }

//Devuelve un "boolean" (0 o 1) dependiendo de si la lista esta vacia o no
int lista_vacia(lista_t lista)  {
    return lista.cantidad == 0;
}

// Inserta el elemento elem en la posicion pos de la lista.
int lista_insertar(lista_t *l, elemento_t *elemen, unsigned int pos){
    if(l -> cantidad >= pos){

        celda_t *celda_nueva;
        celda_nueva = malloc(sizeof(celda_t));
        celda_nueva -> elem = elemen;
        celda_nueva -> siguiente = NULL;

        //Si es en la primera posicion

        if(pos == 0){
            celda_nueva -> siguiente = l -> primera;
            l-> primera = celda_nueva;

            if(lista_vacia(*l) != 0){
                l -> cantidad++;}

        }else{
             //Si es en otra posicion
             celda_t *celda_aux;
             celda_aux = l-> primera;
             celda_t *celda_ant;
             for(int i = 0; i < pos; i++){
                celda_ant = celda_aux;
                celda_aux = celda_aux -> siguiente;}

             if(celda_aux != NULL){
                 celda_nueva -> siguiente = celda_aux -> siguiente;
                 celda_ant -> siguiente = celda_nueva;
                 free(celda_aux);
             } else{
                    l->cantidad = l->cantidad + 1;
                    celda_ant -> siguiente = celda_nueva;
                    }
             }
            return 1;
    }

    return 0;
}

//Elimina el elemento de la posicion pos de la lista.
elemento_t* lista_eliminar(lista_t *l, unsigned int pos){
    if(l->cantidad > pos){
        elemento_t *devolver = malloc(sizeof(elemento_t));
        celda_t *celda_aux;
        if(pos == 0){
            celda_aux = l-> primera;
            l -> primera = (l-> primera) -> siguiente;
        }
        else{
            celda_aux = l-> primera;
            celda_t *celda_ant = NULL;

            for(int i = 0; i < pos; i++){
                celda_ant = celda_aux;
                celda_aux = celda_aux -> siguiente;}

            celda_ant -> siguiente = celda_aux -> siguiente;
        }

        devolver = celda_aux-> elem;
        free(celda_aux);
        l ->cantidad = l->cantidad - 1;
        return devolver;
    }
    return NULL;
}



//Devuelve la cantidad de elementos de la lista l.
unsigned int lista_cantidad(lista_t *l) {
    return l->cantidad;
}

//intercambia los elementos de dos posiciones de la lista.
void lista_intercambiar(lista_t *l,int pos1, int pos2){
    elemento_t * e1;
    e1 = lista_elemento(l,pos1);
    lista_insertar(l, lista_elemento(l,pos2), pos1);
    lista_insertar(l, e1, pos2);
}

//Dada la lista l y la funcion comparar ordena la lista de acuerdo al criterio de dicha funcion.
int lista_ordenar(lista_t *l, funcion_comparacion_t comparar){
    //comparacion_elemento_t:comparar (elemento_t *1, elemento_t *2);
    //hecho de mayor a menor (?)
    int correcto = 1;
    do{
        correcto = 1;
        for(int i = 0; i< lista_cantidad(l) - 1; i++){
            if(comparar(lista_elemento(l,i),lista_elemento(l,i+1)) == 0){ //elem1 menor a elem2
                lista_intercambiar(l,i,i+1);
                correcto = 0;}
            else if(comparar(lista_elemento(l,i),lista_elemento(l,i+1)) == 1) {
                    lista_eliminar(l,i+1);
                 }
        }

    } while(!correcto);
    return 0;
}

void lista_recortar(lista_t *l){
    if(lista_cantidad(l)>0){
        elemento_t *act = lista_elemento(l,0);
        elemento_t *ant;
        char *p1;
        char *p2;
        for(int i = 0; i< lista_cantidad(l)-1;i++){
            ant = lista_elemento(l,i);
            act = lista_elemento(l,i+1);
            p1 = act -> b;
            p2 = ant ->b;

            if(strlen(p1)> strlen(p2)){
                lista_eliminar(l,i);
                i--;}
        }
    }

}

//funcion comparador utilizada en lista_ordenar
comparacion_resultado_t funcion_comparacion_ejemplo(elemento_t *elem1, elemento_t *elem2) {
    int devolver = 3;

    //compara la cantidad de veces que la palabra aparece
    if(elem1 -> a > elem2 -> a) {
        devolver = ELEM1_MAYOR_QUE_ELEM2;
    } else if(elem2 -> a > elem1 -> a) {
               devolver = ELEM1_MENOR_QUE_ELEM2;
           }
           //si aparecen la misma cant de veces, ordeno alfabeticamente
           else if (strcmp(elem1 -> b, elem2 -> b) > 0) {
                    devolver = ELEM1_MAYOR_QUE_ELEM2;
                } else if (strcmp(elem1 -> b, elem2 -> b) < 0) {
                          devolver = ELEM1_MENOR_QUE_ELEM2;;
                       }
                       else devolver = ELEM1_IGUAL_QUE_ELEM2;

    return devolver;
}

//fin implementacion


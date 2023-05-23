
#include "lista.h"
struct celda {
elemento_t *elem;
struct celda *siguiente;
};

//^cambiar

//TODO: chequear malloc por nulls, checkear parametros nulos

//implementacion


//Crea una lista vacıa y la devuelve.(SE ABRE UN MALLOC)
lista_t* lista_crear(){
    lista_t *nueva_lista;
    nueva_lista = malloc(sizeof(lista_t));
    nueva_lista -> cantidad =0;
    nueva_lista -> primera = NULL;
    return nueva_lista;
}

int lista_vacia(lista_t lista)  {
    return lista.cantidad == 0;
}

// Inserta el elemento elem en la posicion pos de la lista.
int lista_insertar(lista_t *l, elemento_t elemen, unsigned int pos){
    if(l -> cantidad >= pos){

        celda_t *celda_nueva;
        celda_nueva = malloc(sizeof(celda_t));
        celda_nueva -> elem = &elemen;

        //Si es en la primera posicion

        if(pos == 0){
            celda_nueva -> siguiente = l -> primera -> siguiente;
            free(l-> primera);
            l-> primera = celda_nueva;

            if(lista_vacia(*l) == 0){
                l -> cantidad++;}

        }else{
             //Si es en otra posicion
             celda_t *celda_aux = l-> primera;
             celda_t *celda_ant = NULL;

             for(int i = 0; i < pos; i++){
                celda_ant = celda_aux;
                celda_aux = celda_aux -> siguiente;}

             if(celda_aux != NULL){
                 celda_nueva -> siguiente = celda_aux -> siguiente;
                 celda_ant -> siguiente = celda_nueva;
                 free(celda_aux);}
                 else{
                    l->cantidad = l->cantidad + 1;
                    celda_ant -> siguiente = celda_nueva;}}

            return 1;
        }

        return 0;
}

//Elimina el elemento de la posicion pos de la lista.
elemento_t* lista_eliminar(lista_t *l, unsigned int pos){
    if(l->cantidad > pos){
        elemento_t *devolver;
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

//Devuelve un puntero al elemento que ocupa la posicion pos de la lista
elemento_t* lista_elemento(lista_t *l, unsigned int pos){
    if(l->cantidad > pos){
        celda_t *celda_aux = l-> primera;
        for(int i = 0; i < pos; i++){
            celda_aux = celda_aux -> siguiente;}
        return celda_aux -> elem;}
    else return NULL;}

//Devuelve la cantidad de elementos de la lista l.
unsigned int lista_cantidad(lista_t *l) {
    return l->cantidad;
}

void lista_intercambiar(lista_t *l,int pos1, int pos2){
    elemento_t * e1 = lista_elemento(l,pos1);
    lista_insertar(l, *lista_elemento(l,pos2), pos1);
    lista_insertar(l, *e1, pos2);}

//Dada la lista l y la funcion comparar ordena la lista de acuerdo al criterio de dicha funci´on.
int lista_ordenar(lista_t *l, funcion_comparacion_t comparar){
    //comparacion_elemento_t:comparar (elemento_t *1, elemento_t *2);
    //hecho de mayor a menor (?)
    int correcto = 1;
    do{
        for(int i = 0; i< lista_cantidad(l) -1; i++){
            if(comparar(lista_elemento(l,i),lista_elemento(l,i+1)) == 2){ //elem1 menor a elem2
                lista_intercambiar(l,i,i+1);
                correcto = 0;}
        }

    }while(!correcto);
    return 0;}


//fin implementacion


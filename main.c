
#include "lista.c"
#include "multiset.c"
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#define tamano_palabra_maximo 40
#define max_length 255

//REVISAR: inicializar todo como null
//C:\\Users\\Usuario\\Desktop\\oc

bool tiene_extension_txt (char const *nombre) {
    size_t largo = strlen(nombre);
    return largo > 4 && strcmp(nombre + largo - 4, ".txt") == 0;
}

//metodo que llena un multiset con las palabras del archivo insetado
void llenar_totales (multiset_t *m, char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Error: no se puede abrir el archivo (llenar totales) %s", filename);
    }
    //fgetc leer char
    char buffer[tamano_palabra_maximo];
    char palabra[tamano_palabra_maximo];
    for(int i=0; fgets(buffer, max_length, fp); i++) {
        int j = 0;
        int k = 0;

        while(buffer[j] != '\0' && buffer[j] != '\n'){
            if(buffer[j]>= 97 && buffer[j]<= 122){
                palabra[k] = buffer[j];
                k++;}
            else{
                palabra[k] = '\0';
                multiset_insertar(m, palabra);
                k = 0;
            }
            j++;
        }
        palabra[k] = '\0';
        multiset_insertar(m, palabra);
    }
}


//imprime los contenidos de la lista
void imprimir_lista(lista_t *l, FILE *filename){
    celda_t *actual = malloc(sizeof(celda_t));
    actual = l->primera;
    while(actual != NULL){
        fprintf(filename, "%i",actual-> elem -> a );
        fprintf(filename," ");
        fprintf(filename, actual-> elem -> b);
        fprintf(filename,"\n");

        actual = actual -> siguiente;
    }
}

int main(int argc, char *argv[]) {
    char *dirNombre = malloc(sizeof(char) * 50); //directorios a leer
    //leer textos y una sola vez(sin guardarlos en ninguna lista o array), mientras se leen se sacan
    //las palabras y se guardan en el multiset, luegoo de ese multiset se forma el archivo
    if(argc>=3){
        printf("Pantalla de ayuda de cuentapalabras.exe:\n");
        printf("El programa recibe como parametro una direccion en memoria que contenga archivos de texto y contara la cantidad de\n");
        printf("apariciones de cada palabra dentro de los archivos. En base a esto creara dos archivos, totales.txt y cadauno.txt los cuales\n");
        printf("continen el output del programa. Totales tiene la cantidad de apariciones de todas las palabras en todos los archivos juntos y\n");
        printf("cadauno.txt la cantidad de apariciones por archivo.\n");
        printf("el programa se llama por consola como: cuentapalabras [direccion] o cuentapalabras [-h] [direccion], lo que llama a este texto\n");
        printf("explicativo, ademas de ejecutar el programa.");
        dirNombre= argv[2];
    }
    else{
        dirNombre = argv[1];
    }

    DIR *directorio = malloc(sizeof(DIR));
    directorio = opendir (dirNombre);

    if(directorio == NULL) {
        printf("\ndirectorio invalido");
        return -1;
    }

    struct dirent *ent;//estructura obtenida de readdir
    bool hay_txts = false;
    FILE *fptr_cadauno = fopen ("cadauno.txt", "w");
    FILE *fptr_totales = fopen ("totales.txt", "w");

    multiset_t *totales_m = multiset_crear();

    lista_t *lcu = lista_crear();

    while ((ent = readdir (directorio)) != NULL) {//acceder a textos, mientras haya archivos no analizados
        char *nombre_archivo = ent->d_name;
        multiset_t *cada_uno_m = multiset_crear();
        if(tiene_extension_txt(nombre_archivo) && strcmp(nombre_archivo, "cadauno.txt") && strcmp(nombre_archivo, "totales.txt")) {
            hay_txts = true;
            llenar_totales(totales_m, nombre_archivo);
            llenar_totales(cada_uno_m, nombre_archivo);


            lista_t *lcu2 = lista_crear();



            *lcu2 = multiset_elementos(cada_uno_m, NULL);
            *lcu = multiset_elementos(totales_m, NULL);


            lista_recortar(lcu2);


            lista_ordenar(lcu2, funcion_comparacion_ejemplo);

            fprintf(fptr_cadauno, nombre_archivo);
            fprintf(fptr_cadauno,"\n");
            imprimir_lista(lcu2, fptr_cadauno);

            cada_uno_m = NULL;
        }
    }
    lista_recortar(lcu);
    lista_ordenar(lcu, funcion_comparacion_ejemplo);

    imprimir_lista(lcu, fptr_totales);

    if(hay_txts == false) {
        printf("\nno hay .txts en el directorio indicado");
        return -1;
    }

    fclose(fptr_cadauno);
    fclose(fptr_totales);

    return 0;
}

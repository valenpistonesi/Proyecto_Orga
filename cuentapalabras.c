
#include "lista.c"
#include "multiset.c"
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#define tamano_palabra_maximo 40
#define max_length 255

//REVISAR: inicializar todo como null
//C:\\Users\\Usuario\\Desktop\\orga

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
            j++;}
        palabra[k] = '\0';
        multiset_insertar(m, palabra);}}


//imprime los contenidos de la lista
void imprimir_lista(lista_t *l, FILE *filename){
    celda_t *actual = l->primera;
    while(actual != NULL){
        fprintf(filename, "%i",actual-> elem -> a );
        fprintf(filename,"  ");
        fprintf(filename, actual-> elem -> b);
        fprintf(filename,"\n");

        actual = actual -> siguiente;}
}

int main() {

    //leer textos y una sola vez(sin guardarlos en ninguna lista o array), mientras se leen se sacan
    //las palabras y se guardan en el multiset, luegoo de ese multiset se forma el archivo

    char *dirNombre = malloc(sizeof(char) * 50); //directorios a leer

    printf("Ingrese el directorio a analizar: \n"); //C:\\Users\\usuario\\OneDrive\\Escritorio\\Uni\\ODC\\proyecto
    scanf("%s", dirNombre);

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
    multiset_t *cada_uno_m = multiset_crear();

    while ((ent = readdir (directorio)) != NULL) {//acceder a textos, mientras haya archivos no analizados
        char *nombre_archivo = ent->d_name;
        if(tiene_extension_txt(nombre_archivo) && strcmp(nombre_archivo, "cadauno.txt") && strcmp(nombre_archivo, "totales.txt")) {
            llenar_totales(totales_m, nombre_archivo);
            llenar_totales(cada_uno_m, nombre_archivo);

            lista_t lcu = multiset_elementos(cada_uno_m, NULL);
            printf("%d",lista_cantidad(&lcu));
            lista_ordenar(&lcu, funcion_comparacion_ejemplo);

            fprintf(fptr_cadauno, nombre_archivo);
            fprintf(fptr_cadauno,"\n");
            imprimir_lista(&lcu, fptr_cadauno);


            /*printf(nombre_archivo);
            fprintf(fptr_cadauno, nombre_archivo); // imprimir en archivo de texto
            printf(": \n\n");

            obtener_palabras(nombre_archivo, m, fptr_cadauno, fptr_totales, buffer_g);
            hay_txts = true;
            printf("\n\n");
            fprintf(fptr_cadauno, "\n");*/

        }
    }

    if(hay_txts == false) {
        printf("\nno hay .txts en el directorio indicado");
        return -1;
    }

    fclose(fptr_cadauno);
    fclose(fptr_totales);

    return 0;}

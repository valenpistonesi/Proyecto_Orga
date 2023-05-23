#include <stdio.h>
#include <stdlib.h>
#include "lista.c"
#include "multiset.c"
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#define tamano_palabra_maximo 40
#define max_length 255

bool tiene_extension_txt (char const *nombre) {
    size_t largo = strlen(nombre);
    return largo > 4 && strcmp(nombre + largo - 4, ".txt") == 0;
}

void obtener_palabras(char *filename ,multiset_t *m){
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    char array [7][40], s[100];


    for(int i=0; fgets(buffer, max_length, fp); i++) {
        strcpy(array[i], buffer);
        printf("%s", array[i]);
    }

    /*char palabra[tamano_palabra_maximo +1];
    int j = 0;

    for(int i=0; fgets(buffer, max_length, fp); i++) {//
        if( buffer[i]>=97 && buffer[i]<= 122 && j<tamano_palabra_maximo){
            printf(buffer[i]);
            palabra[j]= buffer[i];
            j++;}
        else{
            palabra[j] = '\0';
            printf("\n");
            j = 0;
            //multiset_insertar(m,palabra);
        }
        //printf("%s", buffer[i]);
    }
    //multiset_insertar(m,palabra);*/
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

    multiset_t *m = multiset_crear();

    struct dirent *ent;//estructura obtenida de readdir
    bool hay_txts = false;

    while ((ent = readdir (directorio)) != NULL) {//acceder a textos
        char *nombre_archivo = ent->d_name;
        if(tiene_extension_txt(nombre_archivo)) {
            printf(nombre_archivo);
            printf(": \n\n");
            obtener_palabras(nombre_archivo, m);
            hay_txts = true;
            printf("\n\n");
        }
    }




    if(hay_txts == false) {
        printf("\nno hay .txts en el directorio indicado");
        return -1;
    }



    /*while (aux.siguiente != NULL) {
        printf(aux.elem.a);
        printf(" | ");
        printf(aux.elem.b);
        aux = aux.siguiente();
    }*/


    //$ cuentapalbras [-h][directorio de entrada]
    /*char *filename = "readme.txt";
    FILE *fp = fopen(filename, "r");
    FILE *fptr = fopen ("nuevo.txt", "w");*/




/*    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    char array [7][40], s[100];

    for(int i=0; fgets(buffer, MAX_LENGTH, fp); i++) {
        strcpy(array[i], buffer);
        fputs(array[i], fptr);
        printf("%s", array[i]);
    }


    printf("%s","   ");

    fclose(fptr);
    // close the file
    fclose(fp);*/
    return 0;


}

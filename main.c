
#include "lista.c"
#include "multiset.c"
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#define tamano_palabra_maximo 40
#define max_length 255

//REVISAR: inicializar todo como null
//

bool tiene_extension_txt (char const *nombre) {
    size_t largo = strlen(nombre);
    return largo > 4 && strcmp(nombre + largo - 4, ".txt") == 0;
}

int obtener_palabras(char *filename ,multiset_t *m, FILE *fptr, FILE *fptr2){
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // reading line by line, max 256 bytes
    char buffer[tamano_palabra_maximo];


    for(int i=0; fgets(buffer, max_length, fp); i++) {
        multiset_insertar(m, buffer);
        fprintf(fptr2, buffer);
        fprintf(fptr, buffer);
    }

    fclose(fp);
    return 0;
}

int main() {

    //leer textos y una sola vez(sin guardarlos en ninguna lista o array), mientras se leen se sacan
    //las palabras y se guardan en el multiset, luegoo de ese multiset se forma el archivo

    char *dirNombre = malloc(sizeof(char) * 50); //directorios a leer

    printf("Ingrese el directorio a analizar: \n"); //C:\\Users\\kunam\\Desktop\\Nacho\\ODC
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
    FILE *fptr_cadauno = fopen ("cadauno.txt", "w");
    FILE *fptr_totales = fopen ("totales.txt", "w");

    while ((ent = readdir (directorio)) != NULL) {//acceder a textos
        char *nombre_archivo = ent->d_name;
        if(tiene_extension_txt(nombre_archivo) && strcmp(nombre_archivo, "cadauno.txt") && strcmp(nombre_archivo, "totales.txt")) {
            printf(nombre_archivo);
            fprintf(fptr_cadauno, nombre_archivo);
            printf(": \n\n");
            fprintf(fptr_cadauno, ": \n");
            obtener_palabras(nombre_archivo, m, fptr_cadauno, fptr_totales);
            hay_txts = true;
            printf("\n\n");
            fprintf(fptr_cadauno, "\n");
        }
    }

    if(hay_txts == false) {
        printf("\nno hay .txts en el directorio indicado");
        return -1;
    }

    fclose(fptr_cadauno);
    fclose(fptr_totales);

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

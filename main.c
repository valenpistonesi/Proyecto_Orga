#include <stdio.h>
#include <stdlib.h>
#include "lista.c"
#include "multiset.c"

int main()
{
    char *filename = "readme.txt";
    FILE *fp = fopen(filename, "r");
    FILE *fptr = fopen ("nuevo.txt", "w");

    if (fp == NULL)
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
    fclose(fp);

    for(int i=0;i<7;i++){
      for(int j=i+1;j<7;j++){
         if(strcmp(array[i],array[j])!=0){
            strcpy(s,array[i]);
            strcpy(array[i],array[j]);
            strcpy(array[j],s);
        } else {
                strcpy(buffer, "2 | ");
                strcat(buffer, array[i]);
                strcpy(array[i], buffer);

                }
        }
    }

    for(int i=0;i<7;i++){
      printf("%s",array[i]);
    }

    return 0;
}


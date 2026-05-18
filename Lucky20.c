#include <stdio.h>
#include "library.h"

int main()
{
    int set;
    FILE *SET;

    printf("---LUCKY20---\n");
    printf("Selecciona un set de domino:\n");
    printf("[1] Set de 6\n");
    printf("[2] Set de 9\n");
    printf("[3] Set de 12\n");
    scanf("%d", &set);

    SET = fopen("setdefichas.bin", "wb");
    SetDeDomino(SET, set);
    fclose(SET);

}
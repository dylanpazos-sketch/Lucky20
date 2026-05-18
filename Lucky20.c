#include <stdio.h>
#include <stdlib.h>
#include<stdlib.h>
#include "library.h"

int main()
{
    int set, jugadores, CID;
    FILE *SET;
    FILE *BANCO;
    FILE *J1, *J2, *J3, *J4;
    char nombres[5][20] = {"J1.bin", "J2.bin", "J3.bin", "J4.bin","Banco.bin"};


    printf("---LUCKY20---\n");
    printf("Selecciona un set de domino:\n");
    printf("[1] Set de 6\n");
    printf("[2] Set de 9\n");
    printf("[3] Set de 12\n");
    scanf("%d", &set);

    SET = fopen("setdefichas.bin", "wb");
    int Fichas = SetDeDomino(SET, set);

    fclose(SET);

    printf("De cuantos jugadores sera esta ronda?\n");
    printf("[1] Solitario");
    printf("[2] Dos jugadores");
    printf("[3] Tres jugadores");
    printf("[4] Cuatro jugadores");
    scanf("%d", &jugadores);

    int listaID[Fichas];
    for(int i = 0; i < Fichas; i++)
    {
        listaID[i] = i+1;
    }
    Barajear(listaID, Fichas);

    int FActual = 0;
    for (int j = 0; j < jugadores; j++ )
    {
        FILE *temp=fopen(nombres[j], "wb");
        fclose(temp);

        for (int k = 0; k < 6;k++ )
        {
            EntregaFichas(listaID[FActual],nombres[j] );
            FActual++;
        }
    }
    FILE *tempB =fopen("Banco.bin", "wb");
    fclose(tempB);

    while(FActual < Fichas)
    {
        EntregaFichas(listaID[FActual],"Banco.bin");
        FActual++;
    }
    printf("Fichas repartidas con exito.\n");


return 0;
}
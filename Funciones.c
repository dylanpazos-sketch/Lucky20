#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int SetDeDomino(FILE *SET, int set)
{
    int ficha[3];
    int parametro, NumDeFichas;
    int ID = 1;

    if (set == 1)
    {
        parametro = 6;
        NumDeFichas = 28;
    }
    else if (set == 2)
    {
        parametro = 9;
        NumDeFichas = 55;
    }
    else
    {
        parametro = 12;
        NumDeFichas = 91;
    }

    SET = fopen("setdefichas.bin","wb");

    for (int i = 0; i <= parametro; i++)
    {
        for (int j = i; j <= parametro; j++)
        {
            ficha[0] = ID;
            ficha[1] = i;
            ficha[2] = j;

            printf("ID:%d, [%d|%d] \n",ficha[0],ficha[1],ficha[2]);
            fwrite(ficha, sizeof(int), 3, SET);
            ID++;
        }
    }

    return NumDeFichas;
}

int EntregaFichas(int IDNums, char mazo[])
{

    FILE *SET = fopen("setdefichas.bin","rb");
    FILE *Jugador = fopen(mazo,"ab");
    int ficha[3];

    if (SET == NULL || Jugador == NULL)
    {
        printf("Error al abrir algun archivo");
        return 0;
    }

    fseek(SET,(IDNums - 1)*sizeof(int)*3,SEEK_SET);
    fread(ficha,sizeof(int),3,SET);
    fwrite(ficha,sizeof(int),3,Jugador);

    fclose(SET);
    fclose(Jugador);
}

int Barajear(int mazo[],int total)
{
    srand(time(NULL));
    for (int i = total - 1; i > 0; i--)
    {
        int j = rand() % (i+1);

        int temporal = mazo[j];
        mazo[i] = mazo[j];
        mazo[j] = temporal;
    }
}

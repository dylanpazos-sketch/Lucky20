#include<stdio.h>


int SetDeDomino(FILE *SET, int set)
{
    int ficha[3];
    int parametro;
    int ID = 1;

    if (set == 1)
    {
        parametro = 6;
    }
    else if (set == 2)
    {
        parametro = 9;
    }
    else
    {
        parametro = 12;
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

    int Repartir()
}
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

        int temporal = mazo[i];
        mazo[i] = mazo[j];
        mazo[j] = temporal;
    }
}

int MostrarFichas(char NombreArchivo[])
{
    FILE *Archivo = fopen(NombreArchivo,"rb");
    int ficha[3];

    if (Archivo == NULL)
    {
        printf("Error al abrir algun archivo");
        return 1;
    }
    printf("Fichas de %s",NombreArchivo);

    while (fread(ficha,sizeof(int),3,Archivo))
    {
        printf("[%d|%d]",ficha[1],ficha[2]);
    }

    fclose(Archivo);
}

int SumaFicha(int caraA, int caraB,int PuntosFaltantes)
{
    if (caraA != 0 && caraB != 0)
    {
        return caraA + caraB;
    }
    if (caraA == 0 || caraB == 0)
    {
        int valor;
        if (caraA == 0)
        {
            valor =caraB;
        }
        else
        {
            valor = caraA;
        }
        return valor + PuntosFaltantes;
    }
}

int FichasBanco()
{
    FILE *f =fopen("Banco.bin","rb");
    if (f == NULL)
    {
        printf("Error al abrir algun archivo");
        return 1;
    }

    fseek(f,0,SEEK_END);
    long tamano = ftell(f);
    fclose(f);
    return (int)(tamano / (sizeof(int) * 3));
}

int ContarFichas(char nombreArchivo[])
{
    FILE *f = fopen(nombreArchivo, "rb");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long tamano = ftell(f);
    fclose(f);

    return (int)(tamano / (sizeof(int) * 3));
}

int TomarDelBanco(char nombreJugador[])
{
    int TotalBanco = ContarFichas("Banco.bin");

    int Robar;
    if (TotalBanco < 4)
    {
        Robar = TotalBanco;
    }
    else
    {
        Robar = 4;
    }

    for (int i = 0; i < Robar; i++)
    {
        FILE *fBanco = fopen("Banco.bin","rb+");
        FILE *fJugador = fopen(nombreJugador,"ab");
        int ficha[3];

        int TotalActual = ContarFichas("Banco.bin");
        fseek(fBanco,(TotalActual - 1)*sizeof(int)*3,SEEK_SET);

        fread(ficha,sizeof(int),3,fBanco);
        fwrite(ficha,sizeof(int),3,fJugador);

        fclose(fBanco);
        fclose(fJugador);
    }
    printf("Has recibido %d fichas nuevas", Robar);
}

int PonerDos(char NombreJugador[])
{
    int pos1, pos2;

    int total = ContarFichas(NombreJugador);

    if (total < 2) {
        printf("\nNo tienes suficientes fichas para hacer un par.\n");
        return 0;
    }

    printf("\nElige el numero de la primera ficha (1 a %d): ", total);
    scanf("%d", &pos1);
    printf("Elige el numero de la segunda ficha (1 a %d): ", total);
    scanf("%d", &pos2);

    if (pos1 == pos2 || pos1 < 1 || pos2 < 1 || pos1 > total || pos2 > total) {
        printf("Seleccion invalida. Intenta de nuevo.\n");
        return 0;
    }

    int mano[100][3];
    FILE *f = fopen(NombreJugador, "rb");
    for(int i = 0; i < total; i++) {
        fread(mano[i], sizeof(int), 3, f);
    }
    fclose(f);

    int f1a = mano[pos1-1][1];
    int f1b = mano[pos1-1][2];
    int f2a = mano[pos2-1][1];
    int f2b = mano[pos2-1][2];

    int sumaF1 = f1a + f1b;
    int faltante = 20 - sumaF1;

    if (SumaFicha(f2a, f2b, faltante) == 20)
    {
        f = fopen(NombreJugador, "wb");
        for(int i = 0; i < total; i++) {
            if (i != (pos1-1) && i != (pos2-1)) {
                fwrite(mano[i], sizeof(int), 3, f);
            }
        }
        fclose(f);
        printf("\n¡Par validado! Las fichas sumaron 20 y han sido eliminadas.\n");
        return 1;
    }
    else {
        printf("\nEse par no suma 20. Intenta con otras.\n");
        return 0;
    }
}

int PoderSeguirMoviendo(char NombreJugador[])
{
    int total = ContarFichas(NombreJugador);
    if (total < 2)
    {
        return 0;
    }
    int mano[100][3];
    FILE *f = fopen(NombreJugador, "rb");
    for(int i = 0; i < total; i++)
    {
        fread(mano[i], sizeof(int), 3, f);
    }
    fclose(f);
    for (int i = 0; i < total; i++)
    {
        for (int j = i + 1; j < total; j++)
        {
            int f1a = mano[i][1], f1b = mano[i][2];
            int f2a = mano[j][1], f2b = mano[j][2];

            int sumaPuntosFijos = f1a + f1b + f2a + f2b;

            if (f1a != 0 && f1b != 0 && f2a != 0 && f2b != 0)
            {
                if (sumaPuntosFijos == 20) return 1;
            }
            else
            {
                if (sumaPuntosFijos <= 20)
                {
                    return 1;
                }
            }
        }
    }
}
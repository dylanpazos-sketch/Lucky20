#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

int SetDeDomino(int set)
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

    FILE *SET = fopen("setdefichas.bin","wb");

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
    fclose(SET);

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
    int i = 1;

    if (Archivo == NULL)
    {
        printf("Error al abrir algun archivo");
        return 1;
    }
    printf("Fichas de %s",NombreArchivo);

    while (fread(ficha,sizeof(int),3,Archivo))
    {
        printf("\n%d-[%d|%d] ",i,ficha[1],ficha[2]);
        i++;
    }

    fclose(Archivo);
    return 0;
}

int SumaFicha(int f1a, int f1b, int f2a, int f2b) {
    int ceros = 0;
    if (f1a == 0) ceros++;
    if (f1b == 0) ceros++;
    if (f2a == 0) ceros++;
    if (f2b == 0) ceros++;

    int sumaCaras = f1a + f1b + f2a + f2b;

    if (ceros == 0)
    {
        return sumaCaras;
    } else
    {
        if (sumaCaras <= 20)
        {
            return 20;
        } else
        {
            return sumaCaras;
        }
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

    if (Robar == 0)
    {
        printf("\nEl banco esta bacio");
        return 0;
    }

    int manoTemporal[100][3];
    FILE *fBanco = fopen("Banco.bin", "rb");
    for (int i = 0; i < TotalBanco; i++) {
        fread(manoTemporal[i], sizeof(int), 3, fBanco);
    }
    fclose(fBanco);

    FILE *fJugador = fopen(nombreJugador, "ab");
    for (int i = 0; i < Robar; i++) {
        fwrite(manoTemporal[TotalBanco - 1 - i], sizeof(int), 3, fJugador);
    }
    fclose(fJugador);

    fBanco = fopen("Banco.bin", "wb");
    for (int i = 0; i < (TotalBanco - Robar); i++) {
        fwrite(manoTemporal[i], sizeof(int), 3, fBanco);
    }
    fclose(fBanco);

    printf("\nHas recibido %d fichas nuevas.\n", Robar);
    return Robar;
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

    if (SumaFicha(f1a, f1b, f2a, f2b) == 20)
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
        printf("\nEse par no suma 20. Suma actual: %d. Intenta con otras.\n", (f1a+f1b+f2a+f2b));
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

            int sumaF1 = f1a + f1b;
            int faltante = 20 - sumaF1;
            if (SumaFicha(f1a, f1b, f2a, f2b) == 20)
            {
                return 1;
            }
        }
    }
    return 0;
}

void GuardarPartida(int turno, int jugs, int st, int acts, int rets[], char nombresJugs[][100])
{
    FILE *f = fopen("guardado.dat", "wb");
    if(!f) return;
    fwrite(&turno, sizeof(int), 1, f);
    fwrite(&jugs, sizeof(int), 1, f);
    fwrite(&st, sizeof(int), 1, f);
    fwrite(&acts, sizeof(int), 1, f);
    fwrite(rets, sizeof(int), 4, f);
    fwrite(nombresJugs, sizeof(char) * 100, jugs, f);
    fclose(f);
    printf("\nPartida guardada. Puedes continuar despues.\n");
}

typedef struct {
    char nombre[100];
    int paresFormados;
    char fecha[11];
}
RegistroGanador;

void GuardarGanadorBinario(char nombre[], int pares)
{
    FILE *f = fopen("historico_ganadores.bin", "ab");
    if (!f) return;

    RegistroGanador reg;
    strcpy(reg.nombre, nombre);
    reg.paresFormados = pares;


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(reg.fecha, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    fwrite(&reg, sizeof(RegistroGanador), 1, f);
    fclose(f);
}

void GenerarNombreArchivo(char nombreFinal[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char base[50];
    sprintf(base, "partida%02d%02d%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    sprintf(nombreFinal, "%s.bin", base);

    int contador = 1;
    while (fopen(nombreFinal, "rb") != NULL) {
        sprintf(nombreFinal, "%s-%d.bin", base, contador);
        contador++;
    }
}
void RegistrarMovimiento(char archivoPartida[], char nombreJug[], int f1[], int f2[]) {
    FILE *f = fopen(archivoPartida, "ab");
    if (!f) return;

    fwrite(nombreJug, sizeof(char), 100, f);
    fwrite(f1, sizeof(int), 3, f);
    fwrite(f2, sizeof(int), 3, f);

    fclose(f);
}

void ActivarModoPrueba(char nombreArchivo[]) {

    int fichasPrueba[6][3] = {
        {101, 5, 5}, {102, 5, 5},
        {103, 6, 4}, {104, 5, 5},
        {105, 0, 5}, {106, 8, 7}
    };

    FILE *f = fopen(nombreArchivo, "wb");
    if (f != NULL) {
        for (int i = 0; i < 6; i++) {
            fwrite(fichasPrueba[i], sizeof(int), 3, f);
        }
        fclose(f);
    }
}


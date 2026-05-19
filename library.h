#ifndef PROYECTO_FINAL_LIBRARY_H
#define PROYECTO_FINAL_LIBRARY_H



typedef struct {
    char nombre[100];
    int paresFormados;
    char fecha[11];
} RegistroGanador;

int SetDeDomino(int set);
int EntregaFichas(int IDNums, char mazo[]);
int Barajear(int mazo[],int total);
int MostrarFichas(char NombreArchivo[]);
int SumaFicha(int f1a, int f1b, int f2a, int f2b);
int FichasBanco();
int ContarFichas(char nombreArchivo[]);
int TomarDelBanco(char nombreJugador[]);
int PonerDos(char NombreJugador[]);
int PoderSeguirMoviendo(char NombreJugador[]);
void GuardarPartida(int turno, int jugs, int st, int acts, int rets[], char nombresJugs[][100]);
void GuardarGanadorBinario(char nombre[], int pares);
void GenerarNombreArchivo(char nombreFinal[]);
void RegistrarMovimiento(char archivoPartida[], char nombreJug[], int f1[], int f2[]);
void ActivarModoPrueba(char nombreArchivoMazo[]);


#endif // PROYECTO_FINAL_LIBRARY_H
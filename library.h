#ifndef PROYECTO_FINAL_LIBRARY_H
#define PROYECTO_FINAL_LIBRARY_H

int SetDeDomino(FILE *SET, int set);
int EntregaFichas(int IDNums, char mazo[]);
int Barajear(int mazo[],int total);
int MostrarFichas(char NombreArchivo[]);
int SumaFicha(int caraA, int caraB,int PuntosFaltantes);
int FichasBanco();
int ContarFichas(char nombreArchivo[]);
int TomarDelBanco(char nombreJugador[]);
int PonerDos(char NombreJugador[]);
int PoderSeguirMoviendo(char NombreJugador[]);

#endif // PROYECTO_FINAL_LIBRARY_H
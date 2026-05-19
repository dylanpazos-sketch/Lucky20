#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "library.h"

int main()
{
    int set, jugadores, CID, opcion,opcion2;
    FILE *SET;
    FILE *BANCO;
    FILE *J1, *J2, *J3, *J4;
    FILE *Guardados;
    char nombres[5][20] = {"J1.bin", "J2.bin", "J3.bin", "J4.bin","Banco.bin"};
    int paresPorJugador[4] = {0, 0, 0, 0};

    while (opcion != 3){

        printf("---LUCKY20---\n");
        printf("[1] Jugar\n");
        printf("[2] Registro de partidas/Guardado\n");
        printf("[3] salir\n");
        printf("Selecciona una opcion:\n");
        scanf("%d", &opcion);

        if(opcion == 1)
        {
            char nombreArchivoPartida[50];
            GenerarNombreArchivo(nombreArchivoPartida);

            FILE *crear = fopen(nombreArchivoPartida, "wb");
            fclose(crear);

            printf("Selecciona un set de domino:\n");
            printf("[1] Set de 6\n");
            printf("[2] Set de 9\n");
            printf("[3] Set de 12\n");
            scanf("%d", &set);

            SET = fopen("setdefichas.bin", "wb");
            int Fichas = SetDeDomino(SET, set);

            fclose(SET);

            printf("De cuantos jugadores sera esta ronda?\n");
            printf("[1] Solitario\n");
            printf("[2] Dos jugadores\n");
            printf("[3] Tres jugadores\n");
            printf("[4] Cuatro jugadores\n");
            scanf("%d", &jugadores);

            char NombreJugadores[jugadores][100];
            for (int i = 0; i < jugadores; i++)
            {
                printf("Ingrese el nombre del jugador:\n");
                scanf("%s", NombreJugadores[i]);
            }

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

            int JugadoresRet[4] = {0,0,0,0};
            int Turno = 0;
            int activos = jugadores;
            int partida = 1;
            while (partida)
            {
                if (JugadoresRet[Turno] == 1)
                {
                    Turno = (Turno + 1) % jugadores;
                    continue;
                }
                printf("\nTurno del jugador: %s",NombreJugadores[Turno]);
                printf("\nFichas en el Banco:%d",FichasBanco());
                MostrarFichas(nombres[Turno]);

                printf("\nQue decea hacer?");
                printf("\n[a] Formar par(suma 20)");
                printf("\n[b] Pedir 4 fichasdel banco");
                printf("\n[c] Retirarse de la partida");
                printf("\n[d] Guardar y pausar partida\n");
                printf("Selecciona una opcion:\n");

                char seleccion;
                getchar();
                scanf("%c", &seleccion);

                if (seleccion == 'a')
                {
                    if (PonerDos(nombres[Turno]) == 1)
                    {
                        paresPorJugador[Turno]++;
                    }
                }
                else if (seleccion == 'b')
                {
                    TomarDelBanco(nombres[Turno]);
                }
                else if (seleccion == 'c')
                {
                    JugadoresRet[Turno] = 1;
                    activos--;
                    printf("El jugador %s se ah retirado\n");
                }
                else if (seleccion == 'd')
                {
                    GuardarPartida(Turno, jugadores, set, activos, JugadoresRet, NombreJugadores);
                    partida = 0;
                    break;
                }

                if (ContarFichas(nombres[Turno]) == 0)
                {
                    printf("\nFelizidades, %s ah ganado la partida",nombres[Turno]);
                    GuardarGanadorBinario(NombreJugadores[Turno], paresPorJugador[Turno]);
                    partida = 0;
                }
                else if (activos == 0)
                {
                    printf("\nTodos los jugadores se retiraron, la partida termino");
                    partida = 0;
                }
                else if (ContarFichas("Banco.bin") == 0 )
                {
                    int alguienPuedeMover = 0;
                    for ( int i = 0; i < jugadores; i++ )
                    {
                        if (JugadoresRet[i] == 0 && PoderSeguirMoviendo(nombres[i]))
                        {
                            alguienPuedeMover = 1;
                            break;
                        }
                    }
                    if (alguienPuedeMover == 0) {
                        printf("\nDERROTA: No hay fichas en el banco ni movimientos posibles.\n");
                        partida = 0;
                    }
                }
                if (partida != 0 )
                {
                    Turno = (Turno + 1) % jugadores;
                }
            }
        }
        else if (opcion == 2)
        {
            FILE *f = fopen("historico_ganadores.bin", "rb");
            if (!f) {
                printf("\nNo hay registros todavia.\n");
            } else {
                RegistroGanador reg;
                printf("\n--- HISTORIAL DE GANADORES ---\n");
                while (fread(&reg, sizeof(RegistroGanador), 1, f)) {
                    printf("Jugador: %s | Pares: %d | Fecha: %s\n", reg.nombre, reg.paresFormados, reg.fecha);
                }
                fclose(f);
            }
        }
    }

    printf("\nGracias por jugar Lucky20.\n");
    printf("Creditos:Profe cecy");
return 0;
}
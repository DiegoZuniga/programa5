#include <stdlib.h>
#include "chess.h"
#include <iostream>
#include <time.h>

using namespace std;

bool revision(string);
void llenarCadena(string *, int);
void completaIntrucciones(int, int, int);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int tam = 1 + rand() % 10;
    Jugador jugador, jugador2;
    int mode = argv[1][0] - 48;
    int player = argv[2][0] - 48;
    int cant = argv[3][0] - 48;
    int tira_primero = 1 + rand() % 2;
    string cadena, cadena2;
    string instrucciones;
    FILE *consola;
    consola = fopen("consola.txt", "r");
    /*ejecutar con ./main modo de creacion(manual o automatico) jugador (1 o 2) cantdadJugadores (1 o 2) en caso de que se requiera, cadena de movimientos*/
    if (argc == 5 && mode == 1)
        cadena = argv[4];
    else
        llenarCadena(&cadena, tam);
    if (player == 1)
        jugador.initJugador(1, 16, mode, cadena);
    else
        jugador.initJugador(4, 13, mode, cadena);

    Chess chess;
    chess.initChess(jugador);
    cout << "cadena de jugadas del jugador 1: " << cadena << endl;

    if (cant == 2)
    {
        if (mode == 1)
            llenarCadena(&cadena2, cadena.length());
        else
            llenarCadena(&cadena2, tam);
        if (player == 1)
            jugador2.initJugador(4, 13, mode, cadena2);
        else
            jugador2.initJugador(1, 16, mode, cadena2);
        cout << "cadena de jugadas del jugador 2: " << cadena2 << endl;
        chess.initChess(jugador2);
    }
    instrucciones = "python pruebas.py " + to_string(cant);
    instrucciones += " " + to_string(player);
    instrucciones += " " + to_string(tira_primero);
    cout << instrucciones << endl;
    system(instrucciones.c_str());
    //string.c_str();
    return 0;
}

bool revision(string cadena)
{
    for (char c : cadena)
    {
        if (c != 'b' && c != 'r')
            return false;
    }
    return cadena.length() <= 20 ? true : false;
}

void llenarCadena(string *cadena, int tam)
{
    char len[] = {'r', 'b'};
    for (int i = 0; i < tam; i++)
        *cadena += len[rand() % 2];
}
void completaIntrucciones(int cant, int jugador, int tira_primero)
{
    FILE *consola;
    consola = fopen("consola.txt", "w");
    fprintf(consola, "python3 pruebas.py %d %d %d", cant, jugador, tira_primero);
    fclose(consola);
}
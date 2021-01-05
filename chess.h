#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <list>
#include "square.h"
#include "Player.h"
using namespace std;

#define ROWS_NUM 4
typedef list<int> lista;

class Chess{
public:
    Square squareBoard[ROWS_NUM][ROWS_NUM];
    Jugador jugador;
    ofstream all, wins;
    map<int, char> colorCell;
    map<int, lista> movesToR;
    map<int, lista> movesToB;

    void initChess(Jugador);
    void crearTablero();
    void abrirArchivos();
    void cerrarArchivos();
    void inicio();
    void printCaminos(int, lista, int, lista);
    lista getNextMoves(int, int);
    void fillWays();
    bool ValidarPosicion(int, int);
};

void Chess::initChess(Jugador p){
    jugador = p;
    crearTablero();
    abrirArchivos();
    crearTablero();
    fillWays();
    inicio();
    cerrarArchivos();
}

void Chess::abrirArchivos(){
    wins.open(jugador.archivo_ganadoras);
    all.open(jugador.archivo_todas);
}

void Chess::cerrarArchivos(){
    wins.close();
    all.close();
}

void Chess::crearTablero(){
    Square square;
    int counter = 1;
    char color;
    //pendiente de revision de rangos e indices
    for (int i = 0; i < ROWS_NUM; i++){
        for (int j = 0; j < ROWS_NUM; j++){
            if ((counter + i) % 2 == 1)
                color = 'r';
            else    color = 'b';
            
            colorCell[counter] = color;
            square.setNumber(counter);
            square.setColor(color);
            squareBoard[i][j] = square;
            counter++;
        }
    }
}

void Chess::inicio(){
    int q0 = jugador.posicion;
    list<int> temp;
    printCaminos(q0, getNextMoves(q0, 0), 0, temp);
}

void Chess::printCaminos(int actual, list<int> moves, int cont, list<int> camino){
    camino.push_back(actual);
    if (cont == jugador.cadena.length() || actual== jugador.pos_ganadora){
        if (actual == jugador.pos_ganadora){
            bool primer = true;
            for (int it : camino){
                if (primer){
                    wins << it;
                    all << it;
                    primer = false;
                }
                else{
                    wins << " " << it;
                    all << " " << it;
                }
            }
            wins << endl;
            all << endl;
            return;
        }
        else{
            bool primer = true;
            for (int it : camino){
                if (primer){
                    all << it;
                    primer = false;
                }
                else    all << " " << it;
            }
            all << endl;
            return;
        }
    }
    else
        for (int it : moves)
            printCaminos(it, getNextMoves(it, cont+1), cont + 1, camino);
}
void Chess::fillWays(){
    //caminos de R first llave, second valor
    for (int i = 0; i < ROWS_NUM; i++){
        for (int j = 0; j < ROWS_NUM; j++){
            lista d,h;
            if (ValidarPosicion(i - 1, j - 1))
                d.push_back(squareBoard[i - 1][j - 1].getNumber());
            
            if (ValidarPosicion(i, j - 1))
                h.push_back(squareBoard[i][j - 1].getNumber());
            
            if (ValidarPosicion(i - 1, j))
                h.push_back(squareBoard[i - 1][j].getNumber());
            
            if (ValidarPosicion(i + 1, j + 1))
                d.push_back(squareBoard[i + 1][j + 1].getNumber());
            
            if (ValidarPosicion(i, j + 1))
                h.push_back(squareBoard[i][j + 1].getNumber());
            
            if (ValidarPosicion(i + 1, j))
                h.push_back(squareBoard[i + 1][j].getNumber());
            
            if (ValidarPosicion(i - 1, j + 1))
                d.push_back(squareBoard[i - 1][j + 1].getNumber());
            
            if (ValidarPosicion(i + 1, j - 1))
                d.push_back(squareBoard[i + 1][j - 1].getNumber());
            
            if (squareBoard[i][j].getColor() == 'r'){
                movesToR[squareBoard[i][j].getNumber()] = d;
                movesToB[squareBoard[i][j].getNumber()] = h;
            }
            else{
                movesToR[squareBoard[i][j].getNumber()] = h;
                movesToB[squareBoard[i][j].getNumber()] = d;
            }
        }
    }
    // cout << "movimientos para B" << endl;
    // for (map<int, lista>::iterator it = movesToB.begin(); it != movesToB.end(); ++it)
    // {
    //     cout << it->first << " : ";
    //     for (int x : it->second)
    //         cout << x << " ";
    //     cout << endl;
    // }
    // cout << "Movimientos para R" << endl;
    // for (map<int, lista>::iterator it = movesToR.begin(); it != movesToR.end(); ++it)
    // {
    //     cout << it->first << " : ";
    //     for (int x : it->second)
    //         cout << x << " ";
    //     cout << endl;
    // }
}
list<int> Chess::getNextMoves(int casilla, int letra){
    if (jugador.cadena[letra] == 'r')
        return movesToR[casilla];
    else
        return movesToB[casilla];
    
}

bool Chess::ValidarPosicion(int i, int j){
    if (i < 0)
        return false;
    if (i >= ROWS_NUM)
        return false;
    if (j < 0)
        return false;
    if (j >= ROWS_NUM)
        return false;
    return true;
}
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <list>
#include "square.h"
#include "Player.h"
#include "SquareMapItem.h"
using namespace std;

#define ROWS_NUM 4

class Chess
{
    Jugador jugador, jugador2;
    map<int, SquareMapItem> squaresMap;
    Square squareBoard[ROWS_NUM][ROWS_NUM];
    ofstream wins, all;
    int totalIterations = 0;

public:
    void initChess(Jugador);
    void initChess(Jugador, Jugador);
    int getTotalIterations();
    void crearTablero();
    void printPlaysFile();
    void abrirArchivos();
    void cerrarArchivos();
    void printPlays(int, int, list<int>, int, list<int>);
    list<int> getNextMoves(int);
    void getSquareMoves();
    void getMoves(int, int);
};

void Chess::initChess(Jugador p)
{
    jugador = p;
}

void Chess::initChess(Jugador p1, Jugador p2)
{
    jugador = p1;
    jugador2 = p2;
}

int Chess::getTotalIterations()
{
    return totalIterations;
}

void Chess::abrirArchivos()
{
    wins.open(jugador.archivo_ganadoras);
    all.open(jugador.archivo_todas);
}

void Chess::cerrarArchivos()
{
    wins.close();
    all.close();
}

void Chess::printPlaysFile()
{
    int q0 = jugador.posicion;
    list<int> temp = {q0};
    printPlays(q0, jugador.pos_ganadora, getNextMoves(q0), 0, temp);
}

list<int> Chess::getNextMoves(int actual)
{
    return squaresMap[actual].getTotalMoves();
}

void Chess::printPlays(int square, int finalState, list<int> nextMoves, int movesCounter, list<int> path)
{
    if (square == finalState)
    {
        if (path.size() <= jugador.maxMovesWin)
        {
            path.push_back(square);
            path.pop_front();
            bool primer = true;
            for (int it : path)
            {
                if (primer)
                {
                    wins << it;
                    all << it;
                    primer = false;
                }
                else
                {
                    wins << " " << it;
                    all << " " << it;
                }
            }
            wins << endl;
            all << endl;
            return;
        }
    }
    else if (movesCounter < jugador.maxMovesPlayer)
    {
        path.push_back(square);
        for (int it : nextMoves)
        {
            if (it != 0)
            {
                totalIterations++;
                movesCounter++;
                printPlays(it, finalState, squaresMap[it].getTotalMoves(), movesCounter, path);
            }
        }
    }
    else if (movesCounter == jugador.maxMovesPlayer)
    {
        bool primer = true;
        path.pop_front();
        for (int it : path)
        {
            if (primer)
            {
                primer = false;
                all << it;
            }
            else
            {
                all << " " << it;
            }
        }
        all << endl;
        return;
    }
}

void Chess::crearTablero()
{
    Square square;
    int counter = 1;
    char color;
    //pendiente de revision de rangos e indices
    for (int i = 0; i < ROWS_NUM; i++)
    {
        for (int j = 0; j < ROWS_NUM; j++)
        {
            SquareMapItem squareMapItem;
            squareMapItem.setRow(i);
            squareMapItem.setColumn(j);
            squaresMap.insert(pair<int, SquareMapItem>(counter, squareMapItem));
            if ((counter + i) % 2 == 1)
            {
                color = 'w';
            }
            else
            {
                color = 'b';
            }
            square.setNumber(counter);
            square.setColor(color);
            squareBoard[i][j] = square;
            counter++;
        }
    }
    getSquareMoves();
}

void Chess::getSquareMoves()
{
    for (int i = 0; i < ROWS_NUM; i++)
    {
        for (int j = 0; j < ROWS_NUM; j++)
        {
            getMoves(i, j);
        }
    }
}

void Chess::getMoves(int row, int col)
{
    int wMoves[4], bMoves[4], totalMoves[8], wMovesCounter = 0, bMovesCounter = 0, totalMovesCounter = 0;
    if (row > 0)
    {
        // Top left
        if (col > 0)
        {
            if (squareBoard[row - 1][col - 1].getColor() == 'w')
            {
                wMoves[wMovesCounter++] = squareBoard[row - 1][col - 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row - 1][col - 1].getNumber();
            }
            else
            {
                bMoves[bMovesCounter++] = squareBoard[row - 1][col - 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row - 1][col - 1].getNumber();
            }
        }
        // Top right
        if (col < ROWS_NUM - 1)
        {
            if (squareBoard[row - 1][col + 1].getColor() == 'w')
            {
                wMoves[wMovesCounter++] = squareBoard[row - 1][col + 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row - 1][col + 1].getNumber();
            }
            else
            {
                bMoves[bMovesCounter++] = squareBoard[row - 1][col + 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row - 1][col + 1].getNumber();
            }
        }
        // Top
        if (squareBoard[row - 1][col].getColor() == 'w')
        {
            wMoves[wMovesCounter++] = squareBoard[row - 1][col].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row - 1][col].getNumber();
        }
        else
        {
            bMoves[bMovesCounter++] = squareBoard[row - 1][col].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row - 1][col].getNumber();
        }
    }
    // Check bottom boundary
    if (row < ROWS_NUM - 1)
    {
        // Bottom left
        if (col > 0)
        {
            if (squareBoard[row + 1][col - 1].getColor() == 'w')
            {
                wMoves[wMovesCounter++] = squareBoard[row + 1][col - 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row + 1][col - 1].getNumber();
            }
            else
            {
                bMoves[bMovesCounter++] = squareBoard[row + 1][col - 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row + 1][col - 1].getNumber();
            }
        }
        // Bottom right
        if (col < ROWS_NUM - 1)
        {
            if (squareBoard[row + 1][col + 1].getColor() == 'w')
            {
                wMoves[wMovesCounter++] = squareBoard[row + 1][col + 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row + 1][col + 1].getNumber();
            }
            else
            {
                bMoves[bMovesCounter++] = squareBoard[row + 1][col + 1].getNumber();
                totalMoves[totalMovesCounter++] = squareBoard[row + 1][col + 1].getNumber();
            }
        }
        // Bottom
        if (squareBoard[row + 1][col].getColor() == 'w')
        {
            wMoves[wMovesCounter++] = squareBoard[row + 1][col].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row + 1][col].getNumber();
        }
        else
        {
            bMoves[bMovesCounter++] = squareBoard[row + 1][col].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row + 1][col].getNumber();
        }
    }
    // Check left boundary
    if (col > 0)
    {
        // Left
        if (squareBoard[row][col - 1].getColor() == 'w')
        {
            wMoves[wMovesCounter++] = squareBoard[row][col - 1].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row][col - 1].getNumber();
        }
        else
        {
            bMoves[bMovesCounter++] = squareBoard[row][col - 1].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row][col - 1].getNumber();
        }
    }
    // Check right boundary
    if (col < ROWS_NUM - 1)
    {
        // Right
        if (squareBoard[row][col + 1].getColor() == 'w')
        {
            wMoves[wMovesCounter++] = squareBoard[row][col + 1].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row][col + 1].getNumber();
        }
        else
        {
            bMoves[bMovesCounter++] = squareBoard[row][col + 1].getNumber();
            totalMoves[totalMovesCounter++] = squareBoard[row][col + 1].getNumber();
        }
    }
    list<int> wmoves(wMoves, wMoves + sizeof(wMoves) / sizeof(int));
    list<int> bmoves(bMoves, bMoves + sizeof(bMoves) / sizeof(int));
    list<int> totalmoves(totalMoves, totalMoves + sizeof(totalMoves) / sizeof(int));
    squareBoard[row][col].setMoveToW(wmoves);
    squareBoard[row][col].setMoveToB(bmoves);
    squareBoard[row][col].setTotalMoves(totalmoves);
    squaresMap.at(squareBoard[row][col].getNumber()).setMoveToW(wmoves);
    squaresMap.at(squareBoard[row][col].getNumber()).setMoveToB(bmoves);
    squaresMap.at(squareBoard[row][col].getNumber()).setTotalMoves(totalmoves);
}

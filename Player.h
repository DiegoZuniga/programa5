#include <stdlib.h>
#include <iostream>
using namespace std;

class Jugador{
public:
	string cadena;
	int posicion;
	int pos_ganadora;
	string archivo_todas;
	string archivo_ganadoras;
	int creationMode;
	int maxMovesWin;
	int maxMovesPlayer;
	void initJugador(int, int, int,string);
	void move();
	int getPosicion();
	void setCadenaMovimientos(string);
	string getCadenaMovimientos();
	void show_cadena();
	void juega(Jugador);
	void juega(int);
};

void Jugador::initJugador(int pos, int gana, int creationMode,string c){
	archivo_todas = "all_plays_p";
	archivo_ganadoras = "jugadas_ganadoras_p";
	cadena=c;
	posicion = pos;
	pos_ganadora = gana;
	if (pos == 1){
		archivo_todas += "1.txt";
		archivo_ganadoras += "1.txt";
	}
	else{
		archivo_todas += "2.txt";
		archivo_ganadoras += "2.txt";
	}
	this->creationMode = creationMode;
	maxMovesPlayer=cadena.length();
	maxMovesWin=cadena.length();
}

int Jugador::getPosicion(){
	return posicion;
}
#include <stdlib.h>
#include <iostream>
using namespace std;

class Jugador{
	public:
		string cadena_movimientos;
		int posicion;
		int pos_ganadora;
		string archivo_todas="all_plays_p";
		string archivo_ganadoras= "jugadas_ganadoras_p";
		int creationMode;
		int maxMovesWin;
		int maxMovesPlayer;
		void initJugador(int,int,int);
		void move();
		int getPosicion();
		void setCadenaMovimientos(string);
		string getCadenaMovimientos();
		void show_cadena();
		void juega(Jugador);
		void juega(int);
};

void Jugador::initJugador(int pos, int gana, int creationMode){
	posicion=pos;
	pos_ganadora=gana;
	if(pos==1)
		archivo_todas+="1.txt";
	else	archivo_todas+="2.txt";
	this->creationMode=creationMode;
	if(this->creationMode==1)
		maxMovesPlayer=10;
	else 	maxMovesPlayer=20;
}
int Jugador::getPosicion(){
	return posicion;
}
void Jugador::setCadenaMovimientos(string cad){
	cadena_movimientos=cad;
}
string Jugador::getCadenaMovimientos(){
	return cadena_movimientos;
}
void Jugador::show_cadena(){
	cout<<cadena_movimientos<<endl;
}

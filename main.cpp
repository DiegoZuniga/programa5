#include <stdlib.h>
#include "Chess.h"
#include <iostream>
#include <time.h>
using namespace std;

int opcion_creacion(){
	int op;
	do{
		cout<<"1. Ingresar la cadena de movimientos"<<endl<<"2. Generar automaticamente"<<endl;
		cout<<"Ingrese la opcion deseada:\t"<<endl;
		cin>>op;
	}while(op!=1 && op!=2);
	return op;
}
int numJugador(){
	int op;
	do{
		cout<<"1. Jugador 1"<<endl<<"2. Jugador 2"<<endl;
		cout<<"Ingrese la opcion deseada:\t"<<endl;
		cin>>op;
	}while(op!=1 && op!=2);
	return op;
}
int opcion_CantJugadores(){
	int cant_jugadores;
	do{
		cout<<"1. 1 jugador"<<endl<<"2. 2 jugadores"<<endl;
		cout<<"Ingrese la opcion deseada:\t"<<endl;
		cin>>cant_jugadores;
	}while(cant_jugadores!=1 && cant_jugadores!=2);
	return cant_jugadores;
}
int tira_primero(){
	return rand()%2;
}
void limite_cadena(int *limite){
	*limite = 1 + rand()%10;
}
void createArray(char **A,int elem){
    *A=(char *)malloc((elem)*sizeof(char));
    if(*A==NULL){
        printf("No hay memoria disponible...\n");
        exit(0);
    }
}
void llena_array(char *movimientos,int limite){
	char r_or_b[]={'r','b'};
	for (int i=0;i<limite;i++)
		movimientos[i]=r_or_b[rand()%2];
}

bool valida_cadena(string movimientos){
	int i;
	for(i=0;i<movimientos.length();i++)
		if(movimientos[i]!='r' && movimientos[i]!='b')
			return false;

	return movimientos.length()<=20 ? true : false;
}

/*
int main()
{
    Chess chess;

    chess.crearTablero();
    chess.abrirArchivos();
    chess.printPlaysFile(2);
    chess.cerrarArchivos();
}
*/


int main(int argc, char *argv[]){
	srand(time(NULL));
	int limite,op,cant_jugadores,primero,num_jugador;
	char *movimientos,*m2;
	string str_movimientos;
	Jugador p1,p2;
	Chess tablero;
	bool cad_correcta;
	op=opcion_creacion();
	num_jugador=numJugador();
	if(num_jugador==1)
		p1=Jugador(1,16,op);
	else	p1=Jugador(4,13,op);
	if(op==1){
		do{
			fflush(stdin);
			cout<<"Ingresa la cadena de movimientos (solo debe contener r's y b's y contener a lo sumo 20 caracteres)"<<endl;
			cin>>str_movimientos;
			cad_correcta=valida_cadena(str_movimientos);
		}while(!cad_correcta);
		limite=str_movimientos.length();
		p1.setCadenaMovimientos(str_movimientos);
	}
	else{
		limite_cadena(&limite);
		createArray(&movimientos,limite);
		llena_array(movimientos,limite);
		str_movimientos=movimientos;
		p1.setCadenaMovimientos(str_movimientos);
		free(movimientos);
	} 
	//el usuario solo tiene control del jugador 1, por lo tanto las tiradas del segundo, de ahuevo deben ser
	//generadas automaticamente
	
	cant_jugadores=opcion_CantJugadores();
	if (cant_jugadores==2){
		if(num_jugador==1)
			p2=Jugador(4,13,op);
		else	p1=Jugador(1,16,op);
		
		primero=tira_primero();
		createArray(&m2,limite);
		llena_array(m2,limite);
		str_movimientos=m2;
		p2.setCadenaMovimientos(str_movimientos);
		free(m2);
		tablero=Chess(p1,p2);
		//prubeas y quizas tendremos que borrar algunas cosas
		/**
		p2.show_cadena();
		if(primero==0)
			p1.juega(p2);
		else	p2.juega(p1);*/
	}
	else {
		tablero=Chess(p1);
		tablero.crearTablero();
		tablero.abrirArchivos();
		tablero.printPlaysFile();
		tablero.cerrarArchivos();
		//p1.juega(1);
	}
	p1.show_cadena();
	cout<<"ya jala mamada"<<endl;
	return 0;
}
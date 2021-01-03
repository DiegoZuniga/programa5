#include <stdlib.h>
#include "Chess.h"
#include <iostream>
#include <time.h>

using namespace std;

bool revision(string);
void llenarCadena(string*);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    cout << argc << endl;
    int mode = argv[1][0] - 48;
    int player = argv[2][0] - 48;
    int cant = argv[3][0] - 48;
    string cadena;
    if (argc == 5 && mode == 1)
    {
        cadena = argv[4];
    }
    else
    {
        llenarCadena(&cadena);
    }
    cout<<cadena<<endl;
    return 0;
}

bool revision(string cadena)
{
    for (char c : cadena)
    {
        if (c != 'b' && c != 'r')
        {
            return false;
        }
    }
    return true;
}

void llenarCadena(string *cadena){
    int tam= 1+rand()%20;
    char len[]={'r','b'};
    for (int i = 0; i < tam; i++)
    {
        *cadena+=len[rand()%2];
    }
}
/* Código fuente y concepto elaborado por:
	>_ Ricardo Velázquez Contreras - rivel_co
	www.include-poetry.com/Equipo/rivel_co/
*/
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <iomanip>
using namespace std;

#define li LARGE_INTEGER

// Versión actual
string ATCRevision = "Activity Test Counter v0.3.1";
// Almacenamiento de tiempos en milisegundos
long long int tiempos[100000];
// Almacenamiento de tiempo para triple estado
long long int TiemposTri[3][100000];
long long int OrdenEspacios[100000];
// Promedio de tiempos actividad/inactividad
long long int PromAct, PromInact;
// True si se analizan solo deltas
bool SoloDeltas;

string RegNombre, 		// Nombre del registro actual
	   RutaRegistro,	// Ruta en donde se guardará el archivo de salida
	   NombreControl,   // Nombre de identificación del animal
	   ExpMes,			// Mes en que se realizó el experimento
	   ExpDia,			// Día en que se realizó el experimento
	   ExpAno;			// Año en que se realizó el experimento

// Cantidad de tiempos registrados
int TiemposCont;
// Tipo del experimento realizado y su nombre completo
string TipoExperimento, TExpCompleto;
// Bandera de experimento identificado
bool ExpIdentif;
// Tiempo que dura la prueba para el evaluador
long long int TrHoras, TrMins, TrSegs, TiempoRegis;
// Caracter de salida con valor default
char CharSalida = '.';
// Caracteres para Plus Maze
char PMOpen,	// Espacios abiertos
	 PMCenter,	// Espacio del centro
	 PMClose;	// Espacios cerrados
// Tiempo de actividad total
long long int TiempoTotal,
			  TiempoActivo, // Tiempo de actividad
			  TiempoOficial;
long long int tPrimero;
long long int MayAct, MayInact;

#include "FAux/Formato.h"
#include "FAux/FormatoReloj.h"
#include "FAux/PorcentajeActividad.h"

#include "MMenu/Cabecera.h"
#include "MMenu/InfoGrlRegistro.h"
#include "MMenu/SobreElPrograma.h"

#include "FConteo/RegistrarDeltas.h"
#include "FConteo/RegistrarDosEstados.h"
#include "FConteo/RegistrarTresEstados.h"
#include "FConteo/ConteoDosEstados.h"
#include "FConteo/ConteoTresEstados.h"
#include "FConteo/InfoConteo.h"

int main(){
	string pVersion = "TITLE " + ATCRevision;
	system(pVersion.c_str());

	bool menu = true;
	int opc;
	while(menu){
		Cabecera("Men\243");
		cout << "    1- Realizar un conteo est\240ndar" << endl
			 << "    2- Realizar un an\240lisis por deltas de tiempo" << endl
			 << "    3- Sobre este programa" << endl
			 << "    4- Salir" << endl
			 << endl
			 << "    N\243mero de tu elecci\242n: ";
		cin >> opc;
		switch(opc){
			case 1:
				SoloDeltas = false;
				InfoConteo();
				break;
			case 2:
				SoloDeltas = true;
				InfoConteo();
				break;
			case 3:
				SobreElPrograma();
				break;
			case 4:
				menu = false;
				break;
			default:
				cout << "    Ingresa una opci\242n v\240lida" << endl;
				break;
		}
	}
	
	return 0;
}

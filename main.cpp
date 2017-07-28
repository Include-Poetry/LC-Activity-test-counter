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
#include <cmath>
#include <queue>
using namespace std;

#define li LARGE_INTEGER

// Versión actual
string ATCRevision = "Activity Test Counter v0.4";
// Almacenamiento de tiempos en milisegundos
long long int tiempos[100000];
// Almacenamiento de tiempo para triple estado
long long int TiemposTri[3][100000];
long long int OrdenEspacios[100000];
// Optimización de tiempos
long double TiemposOpti[100][600];
// Optimización de diferencias
long double TOptiAct[100][600],
			TOptiInact[100][600];
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
long long int EpisodiosAct, EpisodiosInact;

#include "FAux/Formato.h"
#include "FAux/FormatoReloj.h"
#include "FAux/PorcentajeActividad.h"
#include "FAux/ValidarBooleano.h"

#include "MMenu/Cabecera.h"
#include "MMenu/InfoGrlRegistro.h"
#include "MMenu/SobreElPrograma.h"

#include "FConteo/RegistrarDeltas.h"
#include "FConteo/RegistrarDosEstados.h"
#include "FConteo/RegistrarTresEstados.h"
#include "FConteo/PeriodoOptimo.h"
#include "FConteo/DiferenciasOptimasDos.h"
#include "FConteo/ConteoDosEstados.h"
#include "FConteo/ConteoTresEstados.h"
#include "FConteo/InfoConteo.h"

int main(){
	string pVersion = "TITLE " + ATCRevision;
	system(pVersion.c_str());

	bool menu = true, menu2 = true;
	int opc, opc2;
	while(menu){
		Cabecera("Men\243");
		cout << "    1- Realizar un conteo est\240ndar" << endl
			 << "    2- Realizar un an\240lisis por deltas de tiempo" << endl
			 << "    3- Realizar una b\243squeda" << endl
			 << "    4- Sobre este programa" << endl
			 << "    5- Salir" << endl
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
				menu2 = true;
				while (menu2){
					Cabecera("Men\243 de b\243squedas");
					cout << "    1- B\243squeda de bloque \242ptimo de dos estados" << endl
				 		 << "    2- B\243squeda de diferencias \242ptimas de dos estados" << endl
				 		 << "    3- Volver al men\243 anterior" << endl
				 		 << endl
				 		 << "    N\243mero de tu elecci\242n: ";
				 	cin >> opc2;
				 	switch(opc2){
				 		case 1:
				 			PeriodoOptimoDos();
				 			menu2 = false;
				 			break;
				 		case 2:
							DiferenciasOptimasDos();
							menu2 = false;
							break;
						case 3:
							menu2 = false;
						default:
							cout << "    Ingresa una opci\242n v\240lida" << endl;
							break;
				 	}
				}
				break;
			case 4:
				SobreElPrograma();
				break;
			case 5:
				menu = false;
				break;
			default:
				cout << "    Ingresa una opci\242n v\240lida" << endl;
				break;
		}
	}
	
	return 0;
}

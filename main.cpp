/* Source code and concept by:
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
#include <string>
using namespace std;

#define li LARGE_INTEGER
#define MAX 100000

// Por eliminar
long long int MayAct, MayInact, tPrimero;

// Versión actual
string ATCRevision = "Activity Test Counter v0.5";
// Almacenamiento de tiempos en milisegundos
long long int registro[2][100000];
long long int registroMin[2][MAX];
long long int tiempos[100000]; // Por eliminar
// Almacenamiento de tiempo para triple estado
long long int TiemposTri[5][100000];
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
int TiemposContMin;
// Tipo del experimento realizado y su nombre completo
string TipoExperimento, TExpCompleto;
// Bandera de experimento identificado
bool ExpIdentif;
// Variables de interacción social;
bool SIHabituacion;
long long int SILatencyGroo, SILatencyInter;
char SISpaceA,			// Espacios abiertos
	 SISpaceB,			// Espacio del centro
	 SISpaceC,			// Espacios cerrados
	 SIGrooming,		// Espacio donde está el extraño
	 SIInteract;		// Espacio donde está libre
string TipoEspacioA,	// Cadena para espacio A
	   TipoEspacioB,	// Cadena para espacio B
	   TipoEspacioC;	// Cadena para espacio C
// Porque la basura no me deja usar acentos
string TipoEspacioAf,	// Cadena para espacio A
	   TipoEspacioBf,	// Cadena para espacio B
	   TipoEspacioCf,	// Cadena para espacio C
	   TExpCompletof;
// Variables para reconocimiento de objeto
bool ORHabituacion;
int RegistrosORT[2][100000];
long long int ORLatencyGroo, ORLatencyInter;
char ORObjectA,			// Objeto A
	 ORObjectB,			// Objeto B
	 ORGrooming;		// Grooming
string TipoObjetoA,		// Cadena para objeto A
	   TipoObjetoB;		// Cadena para objeto B
// Variable para color dinámico de la consola
string ConsoleColor;
// Tiempo que dura la prueba para el evaluador
long long int TrHoras, TrMins, TrSegs, TiempoRegis;
// Caracter de salida con valor default
char CharSalida = '.';

// Caracteres para Plus Maze
char PMOpen,	// Espacios abiertos
	 PMCenter,	// Espacio del centro
	 PMClose;	// Espacios cerrados
long long int OpenSpace, CloseSpace, CentralSpace; // Tiempo en cada espacio
int OpenIn, CloseIn, CenterIn; // Frecuencia en cada espacio

// Tiempos para dos estados
long long int TiempoTotal,
			  TiempoActivo, // Tiempo de actividad
			  TiempoOficial;
long long int LatenciaAct;
long long int EpisodiosAct, EpisodiosInact;

// Variables de opciones extra
double SpeedFactor = 1;
string Comentario = "";

#include "FAux/Formato.h"
#include "FAux/FormatoReloj.h"
#include "FAux/ActividadDetalle.h"
#include "FAux/FrecuenciaActividad.h"
#include "FAux/LatenciaActividad.h"
#include "FAux/TiempoRealT1.h"
#include "FAux/ValidarBooleano.h"
#include "FAux/AjustarVelocidad.h"
#include "FAux/AgregarComentario.h"
#include "FAux/CompactarActividad.h"
#include "FAux/printPrevious.h"

#include "setControls/setControlsEPM.h"
#include "setControls/setControlsORT.h"
#include "setControls/setControlsTCS.h"
#include "setControls/setControlsExit.h"

#include "setInfo/setDate.h"
#include "setInfo/setDuration.h"
#include "setInfo/setExperiment.h"
#include "setInfo/setExpTypeORT.h"
#include "setInfo/setExpTypeTCS.h"

#include "MMenu/Cabecera.h"
#include "MMenu/InfoGrlRegistro.h"
#include "MMenu/SobreElPrograma.h"

#include "FConteo/RegistrarDeltas.h"
#include "FConteo/ConteoDosEstados.h"
#include "FConteo/RegistrarDosEstados.h"
#include "FConteo/ConteoTresEstados.h"
#include "FConteo/RegistrarTresEstados.h"
#include "FConteo/ConteoTresyDosEstados.h"
#include "FConteo/RegistrarTresyDosEstados.h"
#include "FConteo/ConteoTresEstadosNC.h"
#include "FConteo/RegistrarTresEstadosNC.h"
#include "FConteo/PeriodoOptimo.h"
#include "FConteo/DiferenciasOptimasDos.h"
#include "FConteo/InfoConteo.h"

int main(){
	string pVersion = "TITLE " + ATCRevision;
	system(pVersion.c_str());

	bool menu = true, menu2 = true;
	int opc, opc2;
	while(menu){
		Cabecera("Menu");
		cout << "    1- Perform a regular analisis" << endl
			 << "    2- Perform an analysis using time deltas" << endl
			 << "    3- Perform a search" << endl
			 << "    4- About this program" << endl
			 << "    5- Exit" << endl
			 << endl
			 << "    Number of your choice: ";
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
					Cabecera("Search menu");
					cout << "    1- Search for optimal block in two-state tests" << endl
				 		 << "    2- Search for optimal differences in two-state tests" << endl
				 		 << "    3- Back to main menu" << endl
				 		 << endl
				 		 << "    Number of your choice: ";
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
							cout << "    Enter a valid option" << endl;
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
				cout << "    Enter a valid option" << endl;
				break;
		}
	}
	
	return 0;
}

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

// Almacenamiento de tiempos en milisegundos
long long int tiempos[100000];
// Promedio de timpos actividad/inactividad
long long int PromAct, PromInact;

string RegNombre, 		// Nombre del registro actual
	   NombreControl,   // Nombre de identificación del animal
	   ExpMes,			// Mes en que se realizó el experimento
	   ExpDia,			// Día en que se realizó el experimento
	   ExpAno;			// Año en que se realizó el experimento
// Cantidad de tiempos registrados
int TiemposCont;
// Tipo del experimento realizado
string TipoExperimento;
// Tiempo que dura la prueba para el evaluador
long long int TrHoras, TrMins, TrSegs, TiempoRegis;
// Caracter de salida con valor default
char CharSalida = '.';
// Tiempo de actividad total
long long int TiempoTotal,
			  TiempoActivo, // Tiempo de actividad
			  TiempoOficial;
long long int MayAct, MayInact;
// Cantidad de deltas válidos
long long int DeltasVal;

string Formato(int x, int n){
	// Para dar formato a los numeros tipo reloj
	stringstream ss;
	ss << setw(n) << setfill('0') << x;
	string s = ss.str();
	return s;
}

string FormatoReloj(long long int t){
	int horas, minutos, segundos, mili;
	mili = t%1000;
	t /= 1000;
	segundos = t%60;
	t /= 60;
	minutos = t%60;
	t /= 60;
	horas = t;

	string final = Formato(horas, 2) + ':' + Formato(minutos, 2) + ':' + Formato(segundos, 2) + ':' + Formato(mili, 3);
	return final;
}

double PorcentajeActividad(){
	// Caculamos el porcentaje de tiempo de actividad
	long long int actual;
	TiempoActivo = TiempoTotal = 0;
	int cont = 0, cont2 = 0;
	MayAct = MayInact = 0;
	DeltasVal = -1;

	for (int i=0; i<TiemposCont; i++){
		actual = tiempos[i];
		TiempoTotal += actual;
		
		actual = TiempoTotal >= TiempoRegis ? TiempoRegis - (TiempoTotal - actual) : tiempos[i];
		
		if (DeltasVal == -1){
			if (i%2){
				TiempoActivo += actual;
				cont++;
				if (actual > MayAct) MayAct = actual;
			} else {
				cont2++;
				if (actual > MayInact) MayInact = actual;
			}
		}
		if (DeltasVal == -1 && actual != tiempos[i]){
			DeltasVal = i;
		}
	}
	TiempoOficial = min(TiempoTotal, TiempoRegis);
	double arriba = TiempoActivo, abajo = TiempoOficial;
	double final = (arriba/abajo)*100;
	
	PromAct = TiempoActivo/cont;
	if (cont2 - 1 == 0){
		PromInact = 0;
	} else {
		PromInact = (TiempoOficial-TiempoActivo)/(cont2 - 1);
	}
	
	return final;
}

void Registrar(){
	// Mensaje al usuario de inicio de guardado
	cout << "    Guardando..." << endl;
	
	double pcActivo = PorcentajeActividad();
	// Creamos la variable que será nuestro archivo
	ofstream archivo;
	// Abrimos nuestro archivo, está listo para escribir en él
	archivo.open(RegNombre);
	
	// Calculamos el porcentaje de actividad e inactividad
	
	double pcInactivo = 100 - pcActivo;
	int tPrimero = tiempos[1];

	// Mostramos un resumen de los datos
	archivo << "Animal ID: " << NombreControl << endl
			<< "Prueba realizada: " << TipoExperimento << endl
			<< "Fecha del experimento: " << ExpDia << "-" << ExpMes << "-" << ExpAno << endl << endl
			
			<< "Tiempo especificado por el usuario: " << FormatoReloj(TiempoRegis) << endl
			<< "Tiempo total registrado: " << FormatoReloj(TiempoTotal) << endl << endl
			
			<< "Las siguientes estadísticas se evaluaron en base al tiempo " << FormatoReloj(TiempoOficial) << endl
			<< "dado que es la medida más conveniente a analizar" << endl << endl
			
			<< "Tiempo de actividad: " << FormatoReloj(TiempoActivo) << endl
			<< "Tiempo de inactividad: " << FormatoReloj(TiempoOficial-TiempoActivo) << endl << endl
			
			<< "Porcentaje de actividad: " << pcActivo << " %" << endl
			<< "Porcentaje de inactividad: " << pcInactivo << " %" << endl << endl
			
			<< "Tiempo a primera inactividad: " << FormatoReloj(tPrimero) << endl << endl
			
			<< "Mayor periodo de actividad: " << FormatoReloj(MayAct) << endl
			<< "Mayor periodo de inactivivdad: " << FormatoReloj(MayInact) << endl << endl
			
			<< "Promedio de tiempo activo: " << FormatoReloj(PromAct) << endl
			<< "Promedio de tiempo inactivo: " << FormatoReloj(PromInact) << endl << endl;

	// Mostramos los periodos como se registraron por el usuario
	archivo << "Reporte completo de periodos actividad/inactividad" << endl
			<< "respecto a la duración del video original:" << endl;
	int hora = 0, minuto = 0, segundo = 0, milesima = 0;
	int actual;
	archivo << "-----------------------------------------------------------" << endl
			<< "|     Inicio actividad       |     Inicio inactividad     |" << endl
			<< "-----------------------------------------------------------" << endl;
	long long int acum = 0;
	for (int i=0; i<TiemposCont; i++){
		actual = tiempos[i]; 			// Conversión a entero
		acum += actual;
		// Escribimos la información que se solicita
		archivo << "|     " << FormatoReloj(acum) << "           ";
		// Formato estilo tabla
		if (i%2 == 1)	archivo << "|\n";
	}
	
	// Mostramos las entradas de tiempo originales
	archivo << endl << endl << "Registro completo de deltas de tiempo (ms):" << endl;
	for (int i=0; i<TiemposCont; i++){
		if (i == DeltasVal){
			archivo << "// Fin de tiempo especificado" << endl;
		}
		archivo << tiempos[i] << endl;
	}
	archivo << endl << endl << "Registro realizado con Activity Test Counter v0.1 - rivel_co" << endl
			<< "Fin del reporte" << endl;
	// Terminamos de escribir y cerramos nuestro archivo
	archivo.close();
	
	// Mensaje al usuario de que terminó el guardado
	cout << "    Guardado finalizado" << endl << endl;
	return;
}

void IniciarConteo(){
	// Variables para medir el tiempo
	li freq, t1, t2, t3;
	int i; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;
	
	// Mensaje al usuario de espera
	cout << "    Presiona cualquier tecla cuando comience el video" << endl << endl
		 << "    Cada que el animal cambie de estado activo/inactivo presiona" << endl
		 << "    cualquier tecla excepto " << CharSalida << endl << endl
		 << "    Cuando quieras terminar el registro presiona el caracter " << CharSalida << endl << endl;

	cout << "    Esperando el comienzo de conteo ...";
	
	// Obtenemos la frecuencia
	QueryPerformanceFrequency(&freq);
	
	// Comienza a contar y se indica el tiempo 0
	letra  = getch();
	QueryPerformanceCounter(&t3);
	tiempos[0] = 0;
	
	// Mensaje al usuario de grabación
	cout << endl << "    Contando ...";
	
	// Mientras no excedamos 100000 entradas y no ingresemos el caracter de fin
	for (i=1; letra != CharSalida && i < 100000; i++){
		QueryPerformanceCounter(&t1);		// Definimos el t1
		letra = getch();					// En espera de presionar el botón
		QueryPerformanceCounter(&t2);		// Definimos el t2
		// Calculamos la diferencia de tiempos, en milisegundos y según la frecuencia
		tiempos[i] = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq.QuadPart;
	}
	
	TiemposCont = i;
	
	// Mensaje al usuario de fin del conteo
	cout << endl << "    Conteo terminado" << endl << endl;
	
	Registrar();
}

void SolicitarFecha(){
	cout << "    Ingresa la fecha en que se realiz\242 el experimento" << endl
		 << "    D\241a, mes y a\244o a dos d\241gitos y separados por un espacio: ";
	cin >> ExpDia >> ExpMes >> ExpAno;
	return;
}

void Cabecera(){
	system("cls");
	cout << "------           Activity Test Counter v0.1 por rivel_co           ------" << endl
		 << endl
		 << "                                  Conteo                                 " << endl
		 //<< "     1.- Registrar varios animales de una misma sesi\242n" << endl
		 //<< "     2.- Registrar varios animales de sesiones distintas"  << endl
		 << endl;
		 //<< "     Elecci\242n: ";
}

void Conteo(){
	bool sigue = true;
	while (sigue){
		Cabecera();
		if (ExpDia.size() > 0){
			char opc;
			cout << "    Acabas de usar los siguientes datos generales:" << endl
				 << "    Fecha " << ExpDia << '-' << ExpMes << '-' << ExpAno << endl
				 << "    Experimento " << TipoExperimento << endl
				 << "    Tiempo " << FormatoReloj(TiempoRegis) << endl
				 << "    Caracter de salida " << CharSalida << endl << endl
				 << "    \250Quieres volver a usar todos los datos anteriores? (S/N): ";
			cin >> opc;
			cout << endl;
			if (opc == 'n' || opc == 'N'){
				cout << "    \250Quieres volver a usar la fecha " << ExpDia << '-' << ExpMes << '-' << ExpAno  << "? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					SolicitarFecha();
				}
				cout << endl;
	
				cout << "    \250Quieres volver a usar el tipo de experimento " << TipoExperimento << " ? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					cout << "    Ingresa la prueba a registrar (TST, FST, etc): ";
					cin >> TipoExperimento;
				}
				cout << endl;
				
				cout << "    \250Quieres volver a ajustar a un tiempo de " << FormatoReloj(TiempoRegis) << " ? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					cout << "    Ingresa el tiempo que quieres registrar o al que se ajustar\240 la prueba" << endl
					 	 << "    Ingresa las horas espacio minutos espacio segundos: ";
					cin >> TrHoras >> TrMins >> TrSegs;
					TiempoRegis = (TrHoras*3600000) + (TrMins*60000) + (TrSegs*1000);
				}
				cout << endl;
				
				cout << "    \250Quieres volver a usar el caracter " << CharSalida << " para terminar? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					cout << "    Ingresa el caracter con el que marcar\240s el fin del registro: ";
					cin >> CharSalida;
				}
				cout << endl;
			}
		} else {
			SolicitarFecha();
			cout << endl;
			
			cout << "    Ingresa la prueba a registrar (TST, FST, etc): ";
			cin >> TipoExperimento;
			cout << endl;
			
			cout << "    Ingresa el tiempo que quieres registrar o al que se ajustar\240 la prueba" << endl
				 << "    Ingresa las horas espacio minutos espacio segundos: ";
			cin >> TrHoras >> TrMins >> TrSegs;
			TiempoRegis = (TrHoras*3600000) + (TrMins*60000) + (TrSegs*1000);
			cout << endl;
			
			cout << "    Ingresa el caracter con el que marcar\240s el fin del registro: ";
			cin >> CharSalida;
			cout << endl;
		}
		
		cout << "    Ingresa el nombre control del animal a registrar sin espacios: ";
		cin >> NombreControl;

		// Nombre del archivo de salida
		RegNombre = ExpDia + '-' + ExpMes + '-' + ExpAno + ' ' + TipoExperimento + ' ' + NombreControl;
		// Extensión del archivo de salida
		RegNombre.append(".txt");
		
		Cabecera();
		cout << "    El registro se guardar\240 en el archivo " << RegNombre << endl
			 << "    y en la misma carpeta en donde ejecutaste este programa" << endl << endl;
		
		IniciarConteo();

		char otro;
		cout << "    \250Realizar otro registro? (S/N): ";
		cin >> otro;
		sigue = otro == 's' || otro == 'S';
	}
	return;	
}

int main(){
	system("TITLE Activity Test Counter v0.1");
	Conteo();
	
	return 0;
}
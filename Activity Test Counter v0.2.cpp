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
// Promedio de tiempos actividad/inactividad
long long int PromAct, PromInact;

string RegNombre, 		// Nombre del registro actual
	   RutaRegistro,		// Ruta en donde se guardará el archivo de salida
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
	// Recibe el tiempo en milisegundos como entero y lo convierte en cadena con formato reloj
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

void SolicitarFecha(){
	cout << "    Ingresa la fecha en que se realiz\242 el experimento" << endl
		 << "    D\241a, mes y a\244o a dos d\241gitos y separados por un espacio: ";
	cin >> ExpDia >> ExpMes >> ExpAno;
	return;
}

void Cabecera(){
	system("cls");
	cout << "    ----------           Activity Test Counter v0.2           ----------" << endl
		 << endl
		 << "                                  Conteo                                " << endl
		 << endl;
}

double PorcentajeActividad(){
	// Calculamos el porcentaje de tiempo de actividad
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
	// Creamos la variable que será nuestro archivo
	ofstream archivo;
	// Abrimos nuestro archivo, está listo para escribir en él
	archivo.open(RegNombre);
	
	// Calculamos el porcentaje de actividad	
	double pcActivo = PorcentajeActividad();
	// Calculamos el porcentaje de inactividad
	double pcInactivo = 100 - pcActivo;
	// Determinamos el tiempo a la primer inmovilidad 
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
			<< "Mayor periodo de inactividad: " << FormatoReloj(MayInact) << endl << endl
			
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
	archivo << endl << endl << "Registro realizado con Activity Test Counter v0.2 - rivel_co" << endl
			<< "Fin del reporte" << endl;
	// Terminamos de escribir y cerramos nuestro archivo
	archivo.close();

	return;
}

void IniciarConteo(){
	Cabecera();

	// Variables para medir el tiempo
	li freq, t1, t2, t3;
	int i; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;
	
	// Mensaje al usuario de espera
	cout << "    El archivo se guardar\240 en la carpeta: " << endl
		 << "       " << RutaRegistro << endl
		 << "    y en el archivo: " << endl
		 << "       " << RegNombre << endl
		 << endl 
	     << "    Presiona cualquier tecla cuando comience el video" << endl 
	     << endl
		 << "    Cada que el animal cambie de estado activo/inactivo presiona" << endl
		 << "    cualquier tecla excepto " << CharSalida << endl 
		 << endl
		 << "    Recibir\240s un color de confirmaci\242n del estado del animal" << endl
		 << "       Texto verde -> estado activo" << endl
		 << "       Texto rojo  -> estado inactivo" << endl
		 << endl
		 << "    Cuando quieras terminar el registro presiona el caracter " << CharSalida << endl
		 << endl
		 << "    Esperando el comienzo de conteo ...";
	RegNombre.insert(0, RutaRegistro);
	// Se indica el tiempo 0
	tiempos[0] = 0;
	// Declaración de la bandera de cambio de estados
	bool cambio = true;

	// Obtenemos la frecuencia
	QueryPerformanceFrequency(&freq);
	
	// Comienza a contar en cuanto se reciba entrada
	letra = getch();
	QueryPerformanceCounter(&t3);
	
	// Mensaje al usuario de grabación
	cout << "\n    Contando ...\n";
	
	// Mientras no excedamos 100000 entradas y no ingresemos el caracter de fin
	for (i=1; letra != CharSalida && i < 100000; i++){
		QueryPerformanceCounter(&t1);		// Definimos el t1
		if (cambio){	// Cambio en la bandera
			system("color 0a");		// Color verde = activo
			cambio = false;
		} else {
			system("color 0c");		// Color rojo = inactivo
			cambio = true;
		}
		letra = getch();					// En espera de presionar el botón
		QueryPerformanceCounter(&t2);		// Definimos el t2
		// Calculamos la diferencia de tiempos, en milisegundos y según la frecuencia
		tiempos[i] = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq.QuadPart;
	}
	
	system("color 07");		// Regresamos al blanco y negro

	/*	El primer dígito es el color del fondo y el segundo el del texto

	0 = Negro       8 = Gris
	1 = Azul        9 = Azul claro
	2 = Verde       A = Verde claro
	3 = Aguamarina  B = Aguamarina claro
	4 = Rojo        C = Rojo claro
	5 = Púrpura     D = Púrpura claro
	6 = Amarillo    E = Amarillo claro
	7 = Blanco      F = Blanco brillante	*/	

	// Determinamos la cantidad de cambios de estado
	TiemposCont = i;
	
	// Mensaje al usuario de fin del conteo
	cout << endl << "    Conteo terminado" << endl << endl;
	return;
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
		RegNombre += ".txt";
		
		// Creación de la ruta del archivo de salida
		RutaRegistro = "Registros";
		CreateDirectory(RutaRegistro.c_str(), NULL);
		RutaRegistro += '/' + TipoExperimento;
		CreateDirectory(RutaRegistro.c_str(), NULL);
		RutaRegistro += '/' + ExpDia + '-' + ExpMes + '-' + ExpAno;
		CreateDirectory(RutaRegistro.c_str(), NULL);
		RutaRegistro += '/';

		IniciarConteo();
		// Mensaje al usuario de inicio de guardado
		cout << "    Guardando..." << endl;
		Registrar();	// Guardamos
		// Mensaje al usuario de que terminó el guardado
		cout << "    Guardado finalizado" << endl << endl;

		char otro;
		cout << "    \250Realizar otro registro? (S/N): ";
		cin >> otro;
		sigue = otro == 's' || otro == 'S';
	}
	return;	
}

void SobreElPrograma(){
	// Limpiamos la pantalla
	system("cls");

	cout << "    ----------           Activity Test Counter v0.2           ----------" << endl
		 << endl
		 << endl
		 << "                        Sobre la funci\242n del programa" << endl
		 << endl
		 << "    El programa eval\243a distintas estad\241sticas sobre el tiempo de" << endl
		 << "    actividad e inactividad de un animal experimental en distintas pruebas" << endl
		 << "    de conducta. La versi\242n actual est\240 especialmente enfocada para" << endl
		 << "        TST - Tail Suspension Test" << endl
		 << "        FST - Forced Simming Test" << endl
		 << "    aunque el m\202todo de funcionamiento puede aplicarse tambi\202n a" << endl
		 << "    otras pruebas como Plus Maze"
		 << endl
		 << endl
		 << "                      Sobre el m\202todo de funcionamiento" << endl
		 << endl
		 << "    Para la utilizaci\242n del programa se debe estar observando la prueba" << endl
		 << "    al mismo momento en que se ejecuta el conteo." << endl
		 << "    Una vez que la prueba comienza, el usuario deber\240 pulsar una tecla" << endl
		 << "    cada que el animal cambia de estado inactivo/activo." << endl
		 << "    Para el an\240lisi se da por hecho que el sujeto de prueba comienza con" << endl
		 << "    un estado de actividad." << endl
		 << "    El programa mide el tiempo en que dura el animal en cada estado y en base" << endl
		 << "    a ello realiza el an\240lisis." 
		 << endl
		 << endl
		 << "                       Sobre las estad\241sticas evaluadas" << endl
		 << endl
		 << "    Las estad\241sticas que se realizan en base a los tiempos de cambio son:" << endl
		 << "    - Tiempo total registrado" << endl
		 << "    - Tiempo de evaluaci\242n determinado por el usuario" << endl
		 << "    - Tiempo total de actividad" << endl
		 << "    - Tiempo total de inactividad" << endl
		 << "    - Porcentaje de actividad" << endl
		 << "    - Porcentaje de inactividad" << endl
		 << "    - Tiempo de latencia (a primera inactividad)" << endl
		 << "    - Mayor periodo de actividad" << endl
		 << "    - Mayor periodo de inactividad" << endl
		 << "    - Promedio de tiempo activo" << endl
		 << "    - Promedio de tiempo inactivo" << endl
		 << "    De forma adicional se agrega un reporte completo de:" << endl
		 << "    - Tiempo de cambio de estado respecto a la duraci\242n total del registro" << endl
		 << "    - Registro de deltas de tiempo (tiempo transcurrido en ms entre cada" << endl
		 << "      cambio de estado" << endl
		 << endl
		 << endl
		 << "                        Sobre los archivos de registro" << endl
		 << endl
		 << "    Al finalizar cada registro los archivos se guardan en una ruta como:" << endl
		 << "       Registros/[Nombre de la prueba]/[Fecha del experimento]/" << endl
		 << "    a partir de la ruta en donde se ejecut\242 en programa y en archivo:" << endl
		 << "       [Fecha del experimento] [Nombre de la prueba] [ID del animal].txt" << endl
		 << endl
		 << endl
		 << endl
		 << "    Desarrollado por Ricardo Vel\240zquez Contreras - rivel_co" << endl
		 << endl
		 << endl
		 << "    Presiona cualquier tecla para volver...";
	system("pause>>null");
	return;
}

int main(){
	system("TITLE Activity Test Counter v0.2");
	bool menu = true;
	char opc;
	while(menu){
		system("cls");
		cout << "    ----------           Activity Test Counter v0.2           ----------" << endl
			 << endl
			 << "                                    Men\243" << endl
			 << endl
			 << "    1- Realizar un conteo" << endl
			 << "    2- Sobre este programa" << endl
			 << "    3- Salir" << endl
			 << endl
			 << "    N\243mero de tu elecci\242n: ";
		cin >> opc;
		switch(opc){
			case '1':
				Conteo();
				break;
			case '2':
				SobreElPrograma();
				break;
			case '3':
				menu = false;
				break;
			default:
				cout << "    Ingresa una opci\242n v\240lida" << endl;
				break;
		}
	}
	
	return 0;
}

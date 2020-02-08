// Realiza el conteo con eventos simultaneos, tres eventos principales
// que son excluyentes y otros dos que son excluyentes entre ellos también
// pero simultaneos entre grupos
void ConteoTresyDosEstados(){
	Cabecera("Perform a register");

	// Variables para medir el tiempo
	li freq, t1, t2;
	int i; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;
	// Color de fuente y fondo
	char ColorFont, ColorBg;
	ConsoleColor = "color 07";

	TiemposCont = 0;
	
	// Mensaje al usuario de espera
	InfoGrlRegistro();
	for (int j=0; j<100000; j++){
		registro[0][j] = 0;
		registro[1][j] = 0;
	}
	cout << "    Press a key according to the location/activity of the animal" << endl
		 << "       " << SISpaceA << " -> For " << TipoEspacioA << endl
		 << "       " << SISpaceB << " -> For " << TipoEspacioB << endl
		 << "       " << SISpaceC << " -> For " << TipoEspacioC << endl
		 << "       " << SIGrooming << " -> For grooming" << endl
		 << "       " << SIInteract << " -> For interaction" << endl
		 << "       Any other key to indicate that the animal stopped interaction/grooming" << endl
		 << endl
		 << "    You will get a visual confirmation in a color code" << endl
		 << "       Green font  -> " << TipoEspacioA  << endl
		 << "       Yellow font -> " << TipoEspacioB << endl
		 << "       Red font    -> " << TipoEspacioC << endl
		 << "       Blue background -> Grooming" << endl
		 << "       Gray background -> Interaction" << endl
		 << endl
		 << "    When you want to finish the register press: " << CharSalida << endl
		 << endl
		 << "    Waiting for the start of the register ...";
	RegNombre.insert(0, RutaRegistro);

	// Obtenemos la frecuencia
	QueryPerformanceFrequency(&freq);
	
	// Comienza a contar en cuanto se reciba entrada
	letra = getch();
	
	// Mensaje al usuario de grabación
	cout << "\n    Registering ...\n    ";
	
	// Mientras no excedamos 100000 entradas y no ingresemos el caracter de fin
	for (i=0; letra != CharSalida && i < 100000; i++){
		if (letra == SISpaceA){
			registro[0][i] = 0;
			ConsoleColor[7] = 'a';
			ConsoleColor[6] = '0';
		} else if (letra == SISpaceB){
			registro[0][i] = 1;
			ConsoleColor[7] = 'e';
			ConsoleColor[6] = '0';
		} else if (letra == SISpaceC){
			registro[0][i] = 2;
			ConsoleColor[7] = 'c';
			ConsoleColor[6] = '0';
		} else if (letra == SIGrooming){
			registro[0][i] = 3;
			ConsoleColor[6] = '1';
		} else if (letra == SIInteract){
			registro[0][i] = 4;
			ConsoleColor[6] = '8';
		} else {
			if (i>0){
				registro[0][i] = 5;
			} else {
				// Se maneja de esta forma en caso de ingresar un caracter desconocido al inicio
				// se da por hecho que entra en el espacio B, se registra y muestra
				registro[0][i] = 1;	
				ConsoleColor[7] = 'e';
			}
			ConsoleColor[6] = '0';
		}
		system(ConsoleColor.c_str());		// Marcamos el nuevo color
		QueryPerformanceCounter(&t1);		// Definimos el t1
		letra = getch();					// En espera de presionar el botón
		QueryPerformanceCounter(&t2);		// Definimos el t2
		// Calculamos la diferencia de tiempos, en milisegundos y según la frecuencia
		registro[1][i] = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq.QuadPart;
	}
	system("color 07");		// Regresamos al blanco y negro

	// Determinamos la cantidad de cambios de estado
	TiemposCont = i;
	
	// Mensaje al usuario de fin del conteo
	cout << endl << "    End of the register" << endl << endl;
	return;
}
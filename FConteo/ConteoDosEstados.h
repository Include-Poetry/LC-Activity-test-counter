// Realiza el conteo estándar con dos estados
// Conteo Two-States-Active (empieza con actividad)
// 'ActIni' es la actividad con la que inicia 0/1
//          donde 0 es activo y 1 es inactivo
void ConteoDosEstados(int ActIni){
	Cabecera("Perform a register");

	// Variables para medir el tiempo
	li freq, t1, t2;
	int i=0; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;

	// Inicializamos el arreglo de registro
	for (int j=0; j<100000; j++){
		registro[0][j] = 0;
		registro[1][j] = 0;
	}
	
	// Mensaje al usuario de espera
	InfoGrlRegistro();
	cout << "    Press any key when you want to start the register" << endl 
	     << endl
		 << "    Any time the animal change its state (active/inactive)" << endl
		 << "    press any key except: " << CharSalida << endl 
		 << endl
		 << "    You will get a visual confirmation in a color code" << endl
		 << "       Green font -> active state" << endl
		 << "       Red font   -> inactive state" << endl
		 << endl
		 << "    When you want to finish the register press: " << CharSalida << endl
		 << endl
		 << "    Waiting for the start of the register ...";
	RegNombre.insert(0, RutaRegistro);

	// Variable control de actividad
	int actividad = ActIni;

	// Obtenemos la frecuencia
	QueryPerformanceFrequency(&freq);
	
	// Comienza a contar en cuanto se reciba entrada
	letra = getch();
	
	// Mensaje al usuario de grabación
	cout << "\n    Registering ...\n";
	
	// Mientras no excedamos 100000 entradas y no ingresemos el caracter de fin
	for (i=0; letra != CharSalida && i < 100000; i++){
		QueryPerformanceCounter(&t1);		// Definimos el t1
		if (!actividad){	// Cambio en la bandera
			system("color 0a");		// Color verde = activo
		} else {
			system("color 0c");		// Color rojo = inactivo
		}
		letra = getch();					// En espera de presionar el botón
		QueryPerformanceCounter(&t2);		// Definimos el t2
		// Guardamos la actividad que estaba realizando (0 o 1)
		registro[0][i] = actividad;
		// Calculamos la diferencia de tiempos, en milisegundos y según la frecuencia
		registro[1][i] = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq.QuadPart;
		actividad = actividad > 0 ? 0 : 1; // Invertimos el valor de la actividad
	}
	
	system("color 07");		// Regresamos al blanco y negro

	// Determinamos la cantidad de cambios de estado
	TiemposCont = i;
	
	// Mensaje al usuario de fin del conteo
	cout << endl << "    End of the register" << endl << endl;
	return;
}
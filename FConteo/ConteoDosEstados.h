// Realiza el conteo estándar con dos estados

void ConteoDosEstados(){
	Cabecera("Conteo");

	// Variables para medir el tiempo
	li freq, t1, t2;
	int i; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;
	
	// Mensaje al usuario de espera
	InfoGrlRegistro();
	cout << "    Presiona cualquier tecla cuando comience el video" << endl 
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
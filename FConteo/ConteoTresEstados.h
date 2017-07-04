// Realiza el conteo estándar con dos estados

void ConteoTresEstados(){
	Cabecera("Conteo");

	// Variables para medir el tiempo
	li freq, t1, t2;
	int i; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;
	
	// Mensaje al usuario de espera
	InfoGrlRegistro();
	for (int j=0; j<100000; j++){
		TiemposTri[0][j] = 0;
		TiemposTri[1][j] = 0;
		TiemposTri[2][j] = 0;
	}
	cout << "    Presiona una tecla seg\243n la posici\242n del animal" << endl
		 << "       " << PMOpen << " -> Para espacios abiertos" << endl
		 << "       " << PMCenter << " -> Para el espacio central" << endl
		 << "       " << PMClose << " -> Para espacios cerrados" << endl
		 << endl
		 << "    Recibir\240s un color de confirmaci\242n de la posici\242n del animal" << endl
		 << "       Texto verde -> espacio abierto" << endl
		 << "       Texto amarillo -> espacio central" << endl
		 << "       Texto rojo  -> espacio cerrado" << endl
		 << endl
		 << "    Cuando quieras terminar el registro presiona el caracter " << CharSalida << endl
		 << endl
		 << "    Esperando el comienzo de conteo ...";
	RegNombre.insert(0, RutaRegistro);

	// Obtenemos la frecuencia
	QueryPerformanceFrequency(&freq);
	
	// Comienza a contar en cuanto se reciba entrada
	letra = getch();
	
	// Mensaje al usuario de grabación
	cout << "\n    Contando ...\n";
	
	// Mientras no excedamos 100000 entradas y no ingresemos el caracter de fin
	for (i=1; letra != CharSalida && i < 100000; i++){
		if (letra == PMOpen){
			OrdenEspacios[i] = 0;
			system("color 0a");
		} else if (letra == PMCenter){
			OrdenEspacios[i] = 1;
			system("color 0e");
		} else if (letra == PMClose){
			OrdenEspacios[i] = 2;
			system("color 0c");
		} else {
			cout << "\n    Correcci\242n\n";
			OrdenEspacios[i] = 1;
			system("color 0e");
		}
		QueryPerformanceCounter(&t1);		// Definimos el t1
		letra = getch();					// En espera de presionar el botón
		QueryPerformanceCounter(&t2);		// Definimos el t2
		// Calculamos la diferencia de tiempos, en milisegundos y según la frecuencia
		TiemposTri[ OrdenEspacios[i] ][i] = (t2.QuadPart - t1.QuadPart) * 1000.0 / freq.QuadPart;
		if (i == 1) TiemposTri[ OrdenEspacios[i] ][0] = 0;
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
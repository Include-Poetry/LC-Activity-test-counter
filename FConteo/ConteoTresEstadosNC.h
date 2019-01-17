// Conteo con 3 estados excluyentes y no continuos
// Por lo tanto hay una entrada que indica que el evento anterior finalizó

void ConteoTresEstadosNC(){
	Cabecera("Perform a register");

	// Variables para medir el tiempo
	li freq, t1, t2;
	int i; // Para el ciclo
	
	// Caracter de apoyo, será las entradas del usuario
	char letra;
	
	// Mensaje al usuario de espera
	InfoGrlRegistro();
	for (int j=0; j<100000; j++){
		registro[0][j] = 0;
		registro[1][j] = 0;
	}
	cout << "    Press a key according to the activity of the animal" << endl
		 << "       " << ORObjectA << " -> For object " << TipoObjetoA << endl
		 << "       " << ORObjectB << " -> For object " << TipoObjetoB << endl
		 << "       " << ORGrooming << " -> For grooming" << endl
		 << "       Any other key indicates that the animal is inactive" << endl
		 << endl
		 << "    You will get a visual confirmation in a color code" << endl
		 << "       Green font   -> object " << TipoObjetoA  << endl
		 << "       Yellow font  -> object " << TipoObjetoB << endl
		 << "       Red font     -> grooming " << endl
		 << "       Withe font   -> inactive " << endl
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
	cout << "\n    Registering ...\n";
	
	// Mientras no excedamos 100000 entradas y no ingresemos el caracter de fin
	for (i=0; letra != CharSalida && i < 100000; i++){
		if (letra == ORObjectA){
			registro[0][i] = 0;
			system("color 0a");
		} else if (letra == ORObjectB){
			registro[0][i] = 1;
			system("color 0e");
		} else if (letra == ORGrooming){
			registro[0][i] = 2;
			system("color 0c");
		} else {
			registro[0][i] = 3;
			system("color 07");
		}
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
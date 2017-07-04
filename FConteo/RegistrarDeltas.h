// Análisis por deltas de tiempo generados de un reporte anterior

void RegistrarDeltas(int n){
	Cabecera("An\240lisis por deltas");

	InfoGrlRegistro();
	RegNombre.insert(0, RutaRegistro);

	long long int entrada1 = 0, entrada2;
	int iterador = 0;
	if (n == 2){	// Dos estados
		cout << "    Se ha identificado un an\240lisis de dos estados." << endl
			 << "    A continuaci\242n ingrese los deltas de tiempo ya generados." << endl
			 << "    Al finalizar de ingresar los datos, ingrese -1" << endl
			 << "    Omita cualquier linea que no sea un n\243mero." << endl
			 << endl
			 << "    Listo para recibir los datos:" << endl
			 << "    ";
		while (entrada1 != -1){
			cin >> entrada1;
			tiempos[iterador] = entrada1;
			iterador++;
			if (entrada1 != -1) cout << "    ";
		}
		TiemposCont = iterador-1;
	}
	if (n == 3){	// Tres estados
		for (int j=0; j<100000; j++){
			TiemposTri[0][j] = 0;
			TiemposTri[1][j] = 0;
			TiemposTri[2][j] = 0;
		}

		cout << "    Se ha identificado un an\240lisis de tres estados." << endl
			 << "    A continuaci\242n ingrese los deltas de tiempo ya generados." << endl
			 << "    Al finalizar de ingresar los datos, ingrese -1" << endl
			 << "    Omita cualquier linea que no sea un n\243mero." << endl
			 << endl
			 << "    Listo para recibir los datos:" << endl
			 << "    ";
		while (entrada1 != -1){
			cin >> entrada1;
			if (entrada1 != -1) cin >> entrada2;

			OrdenEspacios[iterador] = entrada1;
			TiemposTri[ OrdenEspacios[iterador] ][iterador] = entrada2;
			iterador++;
			if (entrada1 != -1) cout << "    ";
		}
		TiemposCont = iterador-1;
	}
	cout << endl;
	return;
}
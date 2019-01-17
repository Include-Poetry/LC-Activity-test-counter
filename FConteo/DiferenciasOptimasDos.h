// Función que resuelve cuál es el momento óptimo para encontrar
// determinado comportamiento de datos

void DiferenciasOptimasDos(){
	long double nRegistrosAct, nRegistrosInact, nTiempos,
		MenorCant = 2000000, BloqueTam, optiAcumActi, optiAcumInacti,
		optiAcumTemp, optiAcumMay;
	long long int LimSup, LimInf;
	
	Cabecera("Optimal difference");

	/* --------- Registramos la actividad por minuto --------- */
	cout << "    Enter the amount of registers to analyze as active state: ";
	cin >> nRegistrosAct;
	cout << "    Enter the amount of registers to analyze as inactive state: ";
	cin >> nRegistrosInact;
	cout << "    Enter every temporal register (minute/step) of active state" << endl
		 << endl;
	for (int T=0; T < nRegistrosAct; T++){	// Numero de registros activos
		cout << "    Register (" << T+1 << "/" << nRegistrosAct << ") :" << endl;
		cout << "    ";
		cin >> nTiempos;
		MenorCant = min(MenorCant, nTiempos);	// Limite menor de tiempos a tomar
		for (int i=0; i < nTiempos; i++){		// Minutos de ese registro
			cout << "    ";
			cin >> TOptiAct[T][i];	
		}
	}
	cout << endl
		 << "    Enter every temporal register (minute/step) of inactive state" << endl
		 << endl;
	for (int T=0; T < nRegistrosInact; T++){			// Numero de registros inactivos
		cout << "    Register (" << T+1 << "/" << nRegistrosInact << ") :" << endl;
		cout << "    ";
		cin >> nTiempos;
		MenorCant = min(MenorCant, nTiempos);	// Limite menor de tiempos a tomar
		for (int i=0; i < nTiempos; i++){		// Minutos de ese registro
			cout << "    ";
			cin >> TOptiInact[T][i];
			TOptiInact[T][i] = 100 - TOptiInact[T][i];
		}
	}
	cout << endl;

	/* --------- Encontramos el segmento óptimo ---------*/
	bool SigueOpti = true;

	while (SigueOpti){
		cout << "    Ingresa la cantidad de minutos que dura el bloque a encontrar: ";
		cin >> BloqueTam;
		cout << endl;

		if (BloqueTam > MenorCant){		// Advertencia de error
			cout << "    It's not possible to search for a block of lenght " << BloqueTam << endl
				 << "    because there's at least one register shorter than that" << endl
				 << "    Thus the optimal block is the one that goes from " << endl
				 << "    the minute " << FormatoReloj(0) << " to " << FormatoReloj(60000 * MenorCant) << endl
				 << endl
				 << "    Press any key to return to the menu.";
			system("pause>>null");
			return;
		}

		// Los acumuladores de cada bloque
		optiAcumActi = optiAcumInacti = 0;
		// Sumamos el primer bloque de actividad
		for (int T=0; T<nRegistrosAct; T++){
			for (int i=0; i<BloqueTam; i++){
				optiAcumActi += TOptiAct[T][i]; 
			}
		}
		optiAcumActi /= nRegistrosAct; // El promedio de los bloques es el que hablará
		// Sumamos el primer bloque de inactividad
		for (int T=0; T<nRegistrosInact; T++){
			for (int i=0; i<BloqueTam; i++){
				optiAcumInacti += TOptiInact[T][i]; 
			}
		}
		optiAcumInacti /= nRegistrosInact; // El promedio de los bloques es el que se usará
		/*
		| Utilicé los promedios para normalizar en caso de que no sea la misma cantidad
		| de registros de actividad que de inactividad. Si son la misma cantidad entonces
		| se puede utlizar la suma tal cual. 
		*/

		// Aquí guardaremos las diferencias óptimas
		// Una cola para mostrarlas en orden de aparición
		queue<int> optimos;
		optimos.push(0); // El primer bloque empieza en el 0

		// Sacamos la primer diferencia, por ser la primera será la mejor
		optiAcumMay = abs(optiAcumActi - optiAcumInacti);
		// Los límites del primer bloque, del 0 al tamaño del mismo
		LimSup = BloqueTam;
		LimInf = 0;
		/*
		| Lo que sucederá es que se realizarán dos sumas telescópicas
		| Una suma será para el tiempo de actividad, la otra para el de inactividad
		| De cada una se seguirá utilizando el promedio por lo arriba mencionado
		| Por cada bloque se calcula la diferencia y eso se guarda
		*/
		while (LimSup < MenorCant){
			// Suma de la actividad
			for (int i=0; i<nRegistrosAct; i++){
				optiAcumActi -= TOptiAct[i][LimInf];
			}
			for (int i=0; i<nRegistrosAct; i++){
				optiAcumActi += TOptiAct[i][LimSup];
			}
			optiAcumActi /= nRegistrosAct; // Promedio de actividad

			// Suma de la inactividad
			for (int i=0; i<nRegistrosInact; i++){
				optiAcumInacti -= TOptiInact[i][LimInf];
			}
			for (int i=0; i<nRegistrosInact; i++){
				optiAcumInacti += TOptiInact[i][LimSup];
			}
			optiAcumInacti /= nRegistrosInact; // Promedio de la inactividad

			// Se calcula la nueva diferencia
			optiAcumTemp = abs(optiAcumActi - optiAcumInacti);
			if (optiAcumTemp == optiAcumMay){
				// Entra si hay varias diferencias óptimas
				optimos.push(LimInf+1); // Guardamos el inicio de la diferencia
			} else if (optiAcumTemp > optiAcumMay){
				// Entra acá si es una nueva óptima diferencia
				optiAcumMay = optiAcumTemp; // Definimos la nueva diferencia óptima
				optimos.push(LimInf+1); // Guardamos el inicio de ese bloque (+1 por la indexación)
			}
			// Actualizamos los límites del bloque, equivalente a recorrer el bloque
			LimSup++;
			LimInf++;
		}
		// Si sólo encontramos un óptimo
		if (optimos.size() == 1){
			cout << "    The optimal diference goes from minute: " << FormatoReloj(60000 * optimos.front()) 
			     << " to " << FormatoReloj(60000 * (optimos.front() + BloqueTam)) << endl;
		} else { // En caso de que hayan varios óptimos
			cout << "    There's " << optimos.size() << " optimal diferences:" << endl;
			while (!optimos.empty()){
				cout << "      From minute: " << FormatoReloj(60000 * optimos.front()) 
			    	 << " to " << FormatoReloj(60000 * (optimos.front() + BloqueTam)) << endl;
			    optimos.pop();
			}
		}
		// Limpiamos la estructura de los óptimos para los nuevos registros
		while (!optimos.empty()) optimos.pop();	
		cout << endl << "    Do you want to search another diference in these registers? (Y/N): ";
		SigueOpti = ValidarBooleano('Y', 'N');
	}
	
	return;
}
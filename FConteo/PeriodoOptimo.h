// Función que resuelve cuál es el momento óptimo para encontrar
// determinado comportamiento de datos

void PeriodoOptimoDos(){
	long double nRegistros, nTiempos,
		MenorCant = 2000000, BloqueTam, optiAcum, bestBlock;
	long long int LimSup, LimInf;
	bool aux;

	Cabecera("Optimal interval");

	/* --------- Registramos la actividad por minuto --------- */
	cout << "    Enter the amount of registers to analyze: ";
	cin >> nRegistros;

	cout << "    Enter every temporal register (minute/step)" << endl;

	for (int T=0; T < nRegistros; T++){			// Numero de registro
		cout << "    Register (" << T+1 << "/" << nRegistros << ") :" << endl;
		cout << "    ";
		cin >> nTiempos;	// Cantidad de tiempos en el i-ésimo registro

		MenorCant = min(MenorCant, nTiempos);	// Limite menor de tiempos a tomar

		for (int i=0; i < nTiempos; i++){		// Minutos de ese registro
			cout << "    ";
			cin >> TiemposOpti[T][i];	
		}
	}
	cout << endl;

	/* --------- Encontramos el segmento óptimo ---------*/
	bool SigueOpti = true;

	while (SigueOpti){
		cout << "    Do you want to optimize activity or inactivity? (A/I): ";
		aux = ValidarBooleano('A', 'I');

		cout << "    Enter the length of the block to find on minutes : ";
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

		optiAcum = 0;

		// Acumulado de los primeros BloqueTam registros de los nRegistros
		for (int T=0; T<nRegistros; T++){
			for (int i=0; i<BloqueTam; i++){
				optiAcum += TiemposOpti[T][i]; 
			}
		}
		// Aquí guardaremos los bloques óptimos
		// Una cola para mostrarlos en orden de aparición
		queue<int> optimos;
		bestBlock = optiAcum; // Bloque óptimo al principio es el primer bloque
		optimos.push(0); // El primer bloque empieza en el 0

		LimSup = BloqueTam; // El límite superior es el tamaño del bloque
		LimInf = 0;	// El límite inferior es el 0 (al inicio, claro)
		bool comparacion; // Servirá para decidir si buscamos la mayor o menor suma

		// Se realiza suma telescópica, quitando el último y poniendo uno al frente
		while (LimSup < MenorCant){
			// Quitamos el primer tiempo de todos los registros
			for (int i=0; i<nRegistros; i++){
				optiAcum -= TiemposOpti[i][LimInf];
			}
			// Agregamos el que sigue de todos los registros al frente
			for (int i=0; i<nRegistros; i++){
				optiAcum += TiemposOpti[i][LimSup];
			}
			// Si estamos optimizando actividad entonces buscamos la suma más grande
			if (aux) comparacion = optiAcum > bestBlock;
			else comparacion = optiAcum < bestBlock;

			if (optiAcum == bestBlock){
				// Entramos aquí si hay varios bloques óptimos
				optimos.push(LimInf+1); // Metemos el inicio del bloque actual (+1 por la indexación)
			} else if (comparacion){
				// Entramos acá si encontramos un nuevo óptimo
				while (!optimos.empty()) optimos.pop(); // Borramos los repetidos
				optimos.push(LimInf+1);	// Metemos el inicio del bloque actual (+1 por la indexación)
				optiAcum = bestBlock; // Definimos el nuevo óptimo
			}
			// Actualizamos los límites, equivalente a desplazar el bloque
			LimSup++;
			LimInf++;
		}
		// Si sólo encontramos un óptimo
		if (optimos.size() == 1){
			cout << "    The optimal block goes from minute: " << FormatoReloj(60000 * optimos.front()) 
			     << " to " << FormatoReloj(60000 * (optimos.front() + BloqueTam)) << endl;
		} else { // En caso de que hayan varios óptimos
			cout << "    There's " << optimos.size() << " optimal blocks:" << endl;
			while (!optimos.empty()){
				cout << "      From minute: " << FormatoReloj(60000 * optimos.front()) 
			    	 << " to " << FormatoReloj(60000 * (optimos.front() + BloqueTam)) << endl;
			    optimos.pop();
			}
		}
		// Limpiamos la estructura de los óptimos para los nuevos registros
		while (!optimos.empty()) optimos.pop();	
		cout << endl << "    Do you want to search another block in these registers? (Y/N): ";
		SigueOpti = ValidarBooleano('Y', 'N');
	}
	
	return;
}
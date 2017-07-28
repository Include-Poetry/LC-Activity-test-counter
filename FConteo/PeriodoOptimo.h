// Función que resuelve cuál es el momento óptimo para encontrar
// determinado comportamiento de datos

void PeriodoOptimoDos(){
	long double nRegistros, nTiempos,
		MenorCant = 2000000, BloqueTam, optiAcum, BloqueMay;
	long long int LimSup, LimInf;
	bool optiActividad = true, aux;

	char opc;
	Cabecera("Segmento \242ptimo");

	/* --------- Registramos la actividad por minuto --------- */
	cout << "    Ingresa la cantidad de registros a analizar: ";
	cin >> nRegistros;

	cout << "    Ingresa el registro temporal por minuto" << endl;

	for (int T=0; T < nRegistros; T++){			// Numero de registro
		cout << "    Registro (" << T+1 << "/" << nRegistros << ") :" << endl;
		cout << "    ";
		cin >> nTiempos;

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
		cout << "    \250Quieres optimizar actividad (S) o inactividad (N): ";
		aux = ValidarBooleano();

		/*if ((!aux && optiActividad) || (aux && !optiActividad)){
			for (int T=0; T<nRegistros; T++){
				for (int i=0; i<MenorCant; i++){
					TiemposOpti[T][i] = 100 - TiemposOpti[T][i];
				}
			}
		}
		optiActividad = aux;
		cout << endl;*/

		cout << "    Ingresa la cantidad de minutos que dura el bloque a encontrar: ";
		cin >> BloqueTam;
		cout << endl;
		
		if (BloqueTam > MenorCant){		// Advertencia de error
			cout << "    No se puede realizar la b\243squeda de un bloque de " << BloqueTam << endl
				 << "    debido a que hay al menos un registro de menor duraci\242n." << endl
				 << "    Por lo tanto el bloque \242ptimo es el que va del " << endl
				 << "    minuto " << FormatoReloj(0) << " al " << FormatoReloj(60000 * MenorCant) << endl
				 << endl
				 << "    Presiona cualquier tecla para volver al men\243";
			system("pause>>null");
			return;
		}

		optiAcum = 0;

		for (int T=0; T<nRegistros; T++){
			for (int i=0; i<BloqueTam; i++){
				optiAcum += TiemposOpti[T][i]; 
			}
		}

		queue<int> optimos;

		BloqueMay = optiAcum;
		optimos.push(0);

		LimSup = BloqueTam;
		LimInf = 0;
		bool comparacion;

		while (LimSup < MenorCant){
			for (int i=0; i<nRegistros; i++){
				optiAcum -= TiemposOpti[i][LimInf];
			}
			for (int i=0; i<nRegistros; i++){
				optiAcum += TiemposOpti[i][LimSup];
			}

			if (aux) comparacion = optiAcum > BloqueMay;
			else comparacion = optiAcum < BloqueMay;

			if (optiAcum == BloqueMay){
				optimos.push(LimInf+1);
			} else if (comparacion){
				while (!optimos.empty()) optimos.pop();
				optimos.push(LimInf+1);
				optiAcum = BloqueMay;
			}
			
			LimSup++;
			LimInf++;
		}

		if (optimos.size() == 1){
			cout << "    El bloque \242ptimo es del minuto: " << FormatoReloj(60000 * optimos.front()) 
			     << " al " << FormatoReloj(60000 * (optimos.front() + BloqueTam)) << endl;
		} else {
			cout << "    Se han encontrado " << optimos.size() << " bloques \242ptimos:" << endl;
			while (!optimos.empty()){
				cout << "      Del minuto: " << FormatoReloj(60000 * optimos.front()) 
			    	 << " al " << FormatoReloj(60000 * (optimos.front() + BloqueTam)) << endl;
			    optimos.pop();
			}
		}
		while (!optimos.empty()) optimos.pop();	
		cout << endl << "    \250Quieres volver a buscar un bloque en estos registros? (S/N): ";
		SigueOpti = ValidarBooleano();
	}
	
	return;
}
// Función que resuelve cuál es el momento óptimo para encontrar
// determinado comportamiento de datos

void DiferenciasOptimasDos(){
	long double nRegistrosAct, nRegistrosInact, nTiempos,
		MenorCant = 2000000, BloqueTam, optiAcumActi, optiAcumInacti,
		optiAcumTemp, optiAcumMay, BloqueMay;
	long long int LimSup, LimInf;
	bool optiActividad = true, aux;

	char opc;
	Cabecera("Segmento \242ptimo");

	/* --------- Registramos la actividad por minuto --------- */
	cout << "    Ingresa la cantidad de registros a analizar de estado activo: ";
	cin >> nRegistrosAct;

	cout << "    Ingresa la cantidad de registros a analizar de estado inactivo: ";
	cin >> nRegistrosInact;

	cout << "    Ingresa el registro temporal por minuto de estado activo" << endl;

	for (int T=0; T < nRegistrosAct; T++){			// Numero de registro
		cout << "    Registro (" << T+1 << "/" << nRegistrosAct << ") :" << endl;
		cout << "    ";
		cin >> nTiempos;

		MenorCant = min(MenorCant, nTiempos);	// Limite menor de tiempos a tomar

		for (int i=0; i < nTiempos; i++){		// Minutos de ese registro
			cout << "    ";
			cin >> TOptiAct[T][i];	
		}
	}
	cout << endl;

	cout << "    Ingresa el registro temporal por minuto de estado inactivo" << endl;

	for (int T=0; T < nRegistrosInact; T++){			// Numero de registro
		cout << "    Registro (" << T+1 << "/" << nRegistrosInact << ") :" << endl;
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
			cout << "    No se puede realizar la b\243squeda de un bloque de " << BloqueTam << endl
				 << "    debido a que hay al menos un registro de menor duraci\242n." << endl
				 << "    Por lo tanto el bloque \242ptimo es el que va del " << endl
				 << "    minuto " << FormatoReloj(0) << " al " << FormatoReloj(60000 * MenorCant) << endl
				 << endl
				 << "    Presiona cualquier tecla para volver al men\243";
			system("pause>>null");
			return;
		}

		optiAcumActi = optiAcumInacti = 0;

		for (int T=0; T<nRegistrosAct; T++){
			for (int i=0; i<BloqueTam; i++){
				optiAcumActi += TOptiAct[T][i]; 
			}
		}
		optiAcumActi /= nRegistrosAct;

		for (int T=0; T<nRegistrosInact; T++){
			for (int i=0; i<BloqueTam; i++){
				optiAcumInacti += TOptiInact[T][i]; 
			}
		}
		optiAcumInacti /= nRegistrosInact;

		optiAcumMay = abs(optiAcumActi - optiAcumInacti);
		BloqueMay = 0;

		LimSup = BloqueTam;
		LimInf = 0;

		while (LimSup < MenorCant){
			for (int i=0; i<nRegistrosAct; i++){
				optiAcumActi -= TOptiAct[i][LimInf];
			}
			for (int i=0; i<nRegistrosAct; i++){
				optiAcumActi += TOptiAct[i][LimSup];
			}
			optiAcumActi /= nRegistrosAct;
			for (int i=0; i<nRegistrosInact; i++){
				optiAcumInacti -= TOptiInact[i][LimInf];
			}
			for (int i=0; i<nRegistrosInact; i++){
				optiAcumInacti += TOptiInact[i][LimSup];
			}
			optiAcumInacti /= nRegistrosInact;

			optiAcumTemp = abs(optiAcumActi - optiAcumInacti);
			if (optiAcumTemp > optiAcumMay){
				optiAcumMay = optiAcumTemp;
				BloqueMay = LimInf+1;
			}

			LimSup++;
			LimInf++;
		}

		cout << "    El bloque \242ptimo es del minuto: " << FormatoReloj(60000 * BloqueMay) 
			 << " al " << FormatoReloj(60000 * (BloqueMay + BloqueTam)) << endl;

		cout << endl << "    \250Quieres volver a buscar un bloque en estos registros? (S/N): ";
		SigueOpti = ValidarBooleano();
	}
	
	return;
}
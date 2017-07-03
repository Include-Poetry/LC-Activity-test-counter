// Función de conteo estándar de dos estados

void InfoConteo(){
	bool sigue = true;
	while (sigue){
		Cabecera("Datos del conteo");

		if (ExpDia.size() > 0){	// true si ya se había realizado un registro
			char opc;
			cout << "    Acabas de usar los siguientes datos generales:" << endl
				 << "    Fecha " << ExpDia << '-' << ExpMes << '-' << ExpAno << endl
				 << "    Experimento " << TipoExperimento << endl
				 << "    Tiempo " << FormatoReloj(TiempoRegis) << endl
				 << "    Caracter de salida " << CharSalida << endl;
			if (TipoExperimento == "PM"){
				cout << endl
					 << "    Y como indicadores de ubicaci\242n: " << endl
					 << "       " << PMOpen << " -> Para espacios abiertos" << endl
					 << "       " << PMCenter << " -> Para el espacio central" << endl
					 << "       " << PMClose << " -> Para espacios cerrados" << endl;
			}
			cout << endl
				 << "    \250Quieres volver a usar todos los datos anteriores? (S/N): ";
			cin >> opc;
			cout << endl;
			if (opc == 'n' || opc == 'N'){
				string viejoTipo = TipoExperimento;

				cout << "    \250Quieres volver a usar la fecha " << ExpDia << '-' << ExpMes << '-' << ExpAno  << "? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					cout << "    Ingresa la fecha en que se realiz\242 el experimento" << endl
		 				 << "    D\241a, mes y a\244o a dos d\241gitos y separados por un espacio: ";
					cin >> ExpDia >> ExpMes >> ExpAno;
				}
				cout << endl;
	
				cout << "    \250Quieres volver a usar el tipo de experimento " << TipoExperimento << " ? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					cout << "    Ingresa la prueba a registrar (TST, FST, PM): ";
					cin >> TipoExperimento;
				}
				cout << endl;
				
				cout << "    \250Quieres volver a ajustar a un tiempo de " << FormatoReloj(TiempoRegis) << " ? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					cout << "    Ingresa el tiempo que quieres registrar o al que se ajustar\240 la prueba" << endl
					 	 << "    Ingresa las horas espacio minutos espacio segundos: ";
					cin >> TrHoras >> TrMins >> TrSegs;
					TiempoRegis = (TrHoras*3600000) + (TrMins*60000) + (TrSegs*1000);
				}
				cout << endl;
				
				cout << "    \250Quieres volver a usar el caracter " << CharSalida << " para terminar? (S/N): ";
				cin >> opc;
				if (opc == 'n' || opc == 'N'){
					cout << "    Ingresa el caracter con el que marcar\240s el fin del registro: ";
					cin >> CharSalida;
				}
				cout << endl;

				if (viejoTipo == "PM" && TipoExperimento == "PM"){
					cout << "    \250Quieres volver a usar los caracteres: " << endl
						 << "       " << PMOpen << " -> Para espacios abiertos" << endl
						 << "       " << PMCenter << " -> Para el espacio central" << endl
						 << "       " << PMClose << " -> Para espacios cerrados" << endl
						 << "    para marcar las posiciones del animal? (S/N): ";
					cin >> opc;
					if (opc == 'n' || opc == 'N'){
						cout << "    Ingresa el caracter para espacios abiertos: ";
						cin >> PMOpen;
						cout << "    Ingresa el caracter para el espacio central: ";
						cin >> PMCenter;
						cout << "    Ingresa el caracter para espacios cerrados: ";
						cin >> PMClose;
					}
				} else if (viejoTipo != "PM" && TipoExperimento == "PM") {
					cout << "    Se ha identificado la prueba: Plus Maze" << endl
						 << "    Ingresa el caracter para espacios abiertos: ";
					cin >> PMOpen;
					cout << "    Ingresa el caracter para el espacio central: ";
					cin >> PMCenter;
					cout << "    Ingresa el caracter para espacios cerrados: ";
					cin >> PMClose;
					cout << endl;
				}
				cout << endl;
			}
		} else {
			cout << "    Ingresa la fecha en que se realiz\242 el experimento" << endl
		 		 << "    D\241a, mes y a\244o a dos d\241gitos y separados por un espacio: ";
			cin >> ExpDia >> ExpMes >> ExpAno;
			cout << endl;
			
			cout << "    Ingresa la prueba a registrar (TST, FST, PM): ";
			cin >> TipoExperimento;
			cout << endl;
			
			cout << "    Ingresa el tiempo que quieres registrar o al que se ajustar\240 la prueba" << endl
				 << "    Ingresa las horas espacio minutos espacio segundos: ";
			cin >> TrHoras >> TrMins >> TrSegs;
			TiempoRegis = (TrHoras*3600000) + (TrMins*60000) + (TrSegs*1000);
			cout << endl;
			
			cout << "    Ingresa el caracter con el que marcar\240s el fin del registro: ";
			cin >> CharSalida;
			cout << endl;

			if (TipoExperimento == "PM"){
				cout << "    Se ha identificado la prueba: Plus Maze" << endl
					 << "    Ingresa el caracter para espacios abiertos: ";
				cin >> PMOpen;
				cout << "    Ingresa el caracter para el espacio central: ";
				cin >> PMCenter;
				cout << "    Ingresa el caracter para espacios cerrados: ";
				cin >> PMClose;
				cout << endl;
			}
		}
		
		cout << "    Ingresa el nombre control del animal a registrar sin espacios: ";
		cin >> NombreControl;

		// Nombre del archivo de salida
		RegNombre = ExpDia + '-' + ExpMes + '-' + ExpAno + ' ' + TipoExperimento + ' ' + NombreControl;
		// Extensión del archivo de salida
		RegNombre += ".txt";
		
		// Creación de la ruta del archivo de salida
		RutaRegistro = "Registros";
		CreateDirectory(RutaRegistro.c_str(), NULL);
		RutaRegistro += '/' + TipoExperimento;
		CreateDirectory(RutaRegistro.c_str(), NULL);
		RutaRegistro += '/' + ExpDia + '-' + ExpMes + '-' + ExpAno;
		CreateDirectory(RutaRegistro.c_str(), NULL);
		RutaRegistro += '/';

		if (TipoExperimento == "PM"){
			TExpCompleto = "Plus Maze";
			ExpIdentif = true;
			ConteoTresEstados();
			cout << "    Guardando..." << endl;
			RegistrarTresEstados();	// Guardamos
			cout << "    Guardado finalizado" << endl << endl;
		} else if (TipoExperimento == "TST"){
			TExpCompleto = "Tail Suspension Test";
			ExpIdentif = true;
			ConteoDosEstados();
			cout << "    Guardando..." << endl;
			RegistrarDosEstados();	// Guardamos
			cout << "    Guardado finalizado" << endl << endl;
		} else if (TipoExperimento == "FST"){
			TExpCompleto = "Forced Swim Test";
			ExpIdentif = true;
			ConteoDosEstados();
			cout << "    Guardando..." << endl;
			RegistrarDosEstados();	// Guardamos
			cout << "    Guardado finalizado" << endl << endl;
		} else {
			TExpCompleto = "No identificado :c";
			ExpIdentif = false;
			ConteoDosEstados();
			cout << "    Guardando..." << endl;
			RegistrarDosEstados();	// Guardamos
			cout << "    Guardado finalizado" << endl << endl;
		}

		char otro;
		cout << "    \250Realizar otro registro? (S/N): ";
		cin >> otro;
		sigue = otro == 's' || otro == 'S';
	}
	return;	
}
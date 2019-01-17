// Función de conteo estándar de dos estados

void InfoConteo(){
	bool sigue = true;
	while (sigue){
		Cabecera("Registry information");

		if (ExpDia.size() > 0){	// true si ya se había realizado un registro
			printPrevious();
			cout << "    Do you want to use the same general information? (Y/N): ";
			if (ValidarBooleano('N', 'Y')){
				string viejoTipo = TipoExperimento;

				cout << "    Do you want to use the date " << ExpDia << '-' << ExpMes << '-' << ExpAno  << "? (Y/N): ";
				if (ValidarBooleano('N', 'Y')) setDate();
				cout << endl;
	
				cout << "    Do you want to use again the " << TipoExperimento << " test" << " ? (Y/N): ";
				if (ValidarBooleano('N', 'Y')) setExperiment();
				cout << endl;
				
				cout << "    Do you want to use as duration " << FormatoReloj(TiempoRegis) << " ? (Y/N): ";
				if (ValidarBooleano('N', 'Y')) setDuration();
				cout << endl;
				
				if (!SoloDeltas){
					cout << "    Dou you want to use again " << CharSalida << " as exit character? (Y/N): ";
					if (ValidarBooleano('N', 'Y')) setControlsExit();
					cout << endl;
				}
				char same;
				if (TipoExperimento == "EPM"){
					cout << "    It has been identified the test: Elevated Plus Maze" << endl;
					if (!SoloDeltas){
						same = true;
						if (viejoTipo == "EPM"){
							cout << "    Do you want to use again the next characters:" << endl
								 << "       " << PMOpen << " -> For open spaces" << endl
								 << "       " << PMCenter << " -> For central space" << endl
								 << "       " << PMClose << " -> For closed spaces" << endl
								 << "    to indicate the current location? (Y/N): ";
							same = ValidarBooleano('N', 'Y');
						}
						if (same || viejoTipo != "EPM") setControlsEPM();
					}	
				} else if (TipoExperimento == "TCS"){
					cout << "    It has been identified the test: Three Chamber Sociability" << endl
						 << "    Is the test made for habituation or with the stranger? (H/S): ";
					SIHabituacion = ValidarBooleano('H', 'S');
					setExpTypeTCS(SIHabituacion);
					if (!SoloDeltas){
						same = true;
						if (viejoTipo == "TCS"){
							cout << "    Do you want to use the next characters: " << endl
							 << "       " << SISpaceA << " -> For " << TipoEspacioA << endl
							 << "       " << SISpaceB << " -> For " << TipoEspacioB << endl
							 << "       " << SISpaceC << " -> For " << TipoEspacioC << endl
							 << "       " << SIGrooming << " -> For grooming" << endl
							 << "       " << SIInteract << " -> For interaction" << endl
							 << "    to indicate the current location/activity? (Y/N): "
							 << endl;
							 same = ValidarBooleano('N', 'Y');
						}
						if (same || viejoTipo != "TCS") setControlsTCS();
					}
				} else if (TipoExperimento == "ORT"){
					cout << "    It has been identified the test: Object Recognition test" << endl
						 << "    Is the test made for habituation or with the novel object? (H/N): ";
					ORHabituacion = ValidarBooleano('H', 'N');
					setExpTypeORT(ORHabituacion);
					if (!SoloDeltas){
						same = true;
						if (viejoTipo == "ORT"){
							cout << "    Do you want to use again the next characters:" << endl
								 << "       " << ORObjectA << " -> For " << TipoObjetoA << " object" << endl
								 << "       " << ORObjectB << " -> For " << TipoObjetoB << " object" << endl
								 << "       " << ORGrooming << " -> To indicate grooming" << endl
								 << "    to indicate the current location? (Y/N): ";
							same = ValidarBooleano('N', 'Y');
						}
						if (same || viejoTipo != "ORT") setControlsORT();
					}	
				}
				cout << endl;
			}
		} else {
			setDate();
			setExperiment();
			setDuration();
			if (!SoloDeltas) setControlsExit();

			if (TipoExperimento == "EPM"){
				if (!SoloDeltas){
					cout << "    It has been identified the test: Elevated Plus Maze" << endl;
					setControlsEPM();
				}
			} else if (TipoExperimento == "TCS"){
				cout << "    It has been identified the test: Three Chamber Sociability test" << endl
					 << "    Is the test made for habituation or with the stranger? (H/S): ";
				SIHabituacion = ValidarBooleano('H', 'S');
				setExpTypeTCS(SIHabituacion);
				if (!SoloDeltas) setControlsTCS();
			} else if (TipoExperimento == "ORT"){
				cout << "    It has been identified the test: Object Recognition test" << endl
					 << "    Is the test made for habituation or with the novel object? (H/N): ";
				ORHabituacion = ValidarBooleano('H', 'N');
				setExpTypeORT(ORHabituacion);
				if (!SoloDeltas) setControlsORT();
			}
		}
		
		cout << "    Enter the ID of the animal to be registered (without spaces): ";
		cin >> NombreControl;

		// Nombre del archivo de salida
		// Formato `DD-MM-AA XXX-O ID.txt`
		RegNombre = ExpDia + '-' + ExpMes + '-' + ExpAno;
		RegNombre += ' ' + TipoExperimento;
		if (TipoExperimento == "TCS"){
			if (SIHabituacion) RegNombre += "-H";
			else RegNombre += "-S";
		}
		if (TipoExperimento == "ORT"){
			if (ORHabituacion) RegNombre += "-H";
			else RegNombre += "-N";
		}
		RegNombre += ' ' + NombreControl;
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

		if (TipoExperimento == "TST"){
			TExpCompleto = "Tail Suspension Test";
			ExpIdentif = true;
			if (!SoloDeltas) ConteoDosEstados(0);
			else RegistrarDeltas(2);
			cout << "    Saving..." << endl;
			RegistrarDosEstados(1);	// Guardamos
			cout << "    Saved successfully" << endl << endl;
		} else if (TipoExperimento == "FST"){
			TExpCompleto = "Forced Swim Test";
			ExpIdentif = true;
			if (!SoloDeltas) ConteoDosEstados(0);
			else RegistrarDeltas(2);
			cout << "    Saving..." << endl;
			RegistrarDosEstados(1);	// Guardamos
			cout << "    Saved successfully" << endl << endl;
		} else if (TipoExperimento == "HBT"){
			TExpCompleto = "Hole Board Test";
			ExpIdentif = true;
			if (!SoloDeltas) ConteoDosEstados(1);
			else RegistrarDeltas(2);
			cout << "    Saving..." << endl;
			RegistrarDosEstados(0);	// Guardamos
			cout << "    Saved successfully" << endl << endl;
		} else if (TipoExperimento == "EPM"){
			TExpCompleto = "Elevated Plus Maze";
			ExpIdentif = true;
			if (!SoloDeltas) ConteoTresEstados();
			else RegistrarDeltas(3);
			cout << "    Saving..." << endl;
			RegistrarTresEstados();	// Guardamos
			cout << "    Saved successfully" << endl << endl;
		} else if (TipoExperimento == "TCS"){
			TExpCompleto = TExpCompletof = "Three Chamber Sociability test";
			if (SIHabituacion){
				TExpCompleto += " - (habituation)";
			} else {
				TExpCompleto += " - (with stranger)";
			}
			ExpIdentif = true;
			if (!SoloDeltas) ConteoTresyDosEstados();
			else RegistrarDeltas(3);
			cout << "    Saving..." << endl;
			RegistrarTresyDosEstados();	// Guardamos
			cout << "    Saved successfully" << endl << endl;
		} else if (TipoExperimento == "ORT"){
			TExpCompleto = TExpCompletof = "Object Recognition test";
			if (ORHabituacion){
				TExpCompleto += " - (habituation)";
			} else {
				TExpCompleto += " - (with stranger)";
			}
			ExpIdentif = true;
			if (!SoloDeltas) ConteoTresEstadosNC();
			else RegistrarDeltas(3);
			cout << "    Saving..." << endl;
			RegistrarTresEstadosNC();	// Guardamos
			cout << "    Saved successfully" << endl << endl;
		} else {
			TExpCompleto = "Unidentified test";
			ExpIdentif = false;
			if (!SoloDeltas) ConteoDosEstados(0);
			else RegistrarDeltas(2);
			cout << "    Saving..." << endl;
			RegistrarDosEstados(1);	// Guardamos
			cout << "    Saved successfully" << endl << endl;
		}

		if (!SoloDeltas) cout << "    Do another record? (Y/N): ";
		else cout << "    Do another record using deltas? (Y/N): ";
		sigue = ValidarBooleano('Y', 'N');
	}
	return;	
}
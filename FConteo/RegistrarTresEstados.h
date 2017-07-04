// Función que guarda en un archivo los datos obtenidos del conteo

void RegistrarTresEstados(){
	// Creamos la variable que será nuestro archivo
	ofstream archivo;
	// Abrimos nuestro archivo, está listo para escribir en él
	archivo.open(RegNombre);

	// Obtenemos sumatorias temporales
	long long int OpenSpace = 0, CloseSpace = 0, CentralSpace = 0;
	TiempoTotal = 0;

	long long int valido;
	int PosActual;
	int pasa = -1;
	int OpenIn = 0, CloseIn = 0, CenterIn = 0;

	for (int i=0; i < TiemposCont; i++){
		PosActual = OrdenEspacios[i];

		valido = TiemposTri[PosActual][i];
		TiempoTotal += valido;

		valido = TiempoTotal >= TiempoRegis ? TiempoRegis - (TiempoTotal - valido) : TiemposTri[PosActual][i];

		if (pasa == -1){
			switch(PosActual){
				case 0:
					OpenIn++;
					OpenSpace += valido;
					break;
				case 1:
					CenterIn++;
					CentralSpace += valido;
					break;
				case 2:
					CloseIn++;
					CloseSpace += valido;
					break;
			}
		}
		if (pasa == -1 && valido != TiemposTri[PosActual][i]){
			pasa = i;
		}
	}

	TiempoOficial = min(TiempoTotal, TiempoRegis);
	double arriba, abajo = TiempoOficial;
	arriba = OpenSpace;
	double pcOpen = (arriba/abajo)*100;
	arriba = CentralSpace;
	double pcCentral = (arriba/abajo)*100;
	arriba = CloseSpace;
	double pcClose = (arriba/abajo)*100;

	// Mostramos un resumen de los datos
	archivo << "Animal ID: " << NombreControl << endl
			<< "Prueba realizada: " << TipoExperimento << " -> " << TExpCompleto << endl
			<< "Fecha del experimento: " << ExpDia << "-" << ExpMes << "-" << ExpAno << endl << endl

			<< "Tiempo especificado por el usuario: " << FormatoReloj(TiempoRegis) << endl
			<< "Tiempo total registrado: " << FormatoReloj(TiempoTotal) << endl << endl

			<< "Las siguientes estadísticas se evaluaron en base al tiempo: " << FormatoReloj(TiempoOficial) << endl<< endl

			<< "Tiempo en espacios abiertos: " << FormatoReloj(OpenSpace) << endl
			<< "Tiempo en el espacio central: " << FormatoReloj(CentralSpace) << endl
			<< "Tiempo en espacios cerrados: " << FormatoReloj(CloseSpace) << endl<< endl

			<< "Porcentaje en espacios abiertos: " << pcOpen << " %" << endl
			<< "Porcentaje en el espacio central: " << pcCentral << " %" << endl
			<< "Porcentaje en espacios cerrados: " << pcClose << " %" << endl << endl

			<< "Entradas a espacios abiertos: " << OpenIn-1 << endl
			<< "Entradas al espacio central: " << CenterIn << endl
			<< "Entradas a espacios cerrados: " << CloseIn << endl << endl;

	// Mostramos los periodos como se registraron por el usuario
	archivo << "Reporte completo de periodos en espacio abierto/central/cerrado" << endl
			<< "respecto al inicio del registro:" << endl;
	int actual, PosActualF;
	long long int acum = 0;

	archivo << "----------------------------------" << endl
			<< "|      Momento     |   Espacio   |" << endl
			<< "----------------------------------" << endl;
	for (int i=0; i<TiemposCont; i++){
		PosActualF = OrdenEspacios[i];

		actual = TiemposTri[PosActualF][i]; 			// Conversión a entero
		acum += actual;
		// Escribimos la información que se solicita
		archivo << "|   " << FormatoReloj(acum) << "   ";

		PosActualF = OrdenEspacios[i+1];
		if (i+1 == TiemposCont){
			archivo << "|   Termina   |" << endl;
		} else if (PosActualF == 0){
			archivo << "|   Abierto   |" << endl;
		} else if (PosActualF == 1){
			archivo << "|   Central   |" << endl;
		} else if (PosActualF == 2){
			archivo << "|   Cerrado   |" << endl;
		}
	}
	
	// Mostramos las entradas de tiempo originales
	archivo << endl << endl << "Registro completo de deltas de tiempo (ms):" << endl;
	for (int i=0; i<TiemposCont; i++){
		archivo << OrdenEspacios[i] << " " << TiemposTri[ OrdenEspacios[i] ][i] << endl;
	}
	archivo << endl << endl << "Registro realizado con " << ATCRevision << " - rivel_co" << endl
			<< "Fin del reporte" << endl;
	// Terminamos de escribir y cerramos nuestro archivo
	archivo.close();

	return;
}
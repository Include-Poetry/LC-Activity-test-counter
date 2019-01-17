// Función que guarda en un archivo los datos obtenidos del conteo

void RegistrarTresEstados(){
	AgregarComentario();
	AjustarVelocidad();
	// Creamos la variable que será nuestro archivo
	ofstream archivo;
	// Abrimos nuestro archivo, está listo para escribir en él
	archivo.open(RegNombre.c_str());

	// Calculamos el tiempo real de registro y se selecciona el oficial
	TiempoTotal = TiempoRealT1();
	TiempoOficial = min(TiempoTotal, TiempoRegis);

	// Mostramos un resumen de los datos
	archivo << "Animal ID: " << NombreControl << endl
			<< "Test performed: " << TipoExperimento << " -> " << TExpCompleto << endl
			<< "Test date: " << ExpDia << "-" << ExpMes << "-" << ExpAno << endl
			<< "Aditional comments: " << Comentario << endl
			<< endl
			<< "Test duration specified by user: " << FormatoReloj(TiempoRegis) << endl
			<< "Total time registered: " << FormatoReloj(TiempoTotal) << endl
			<< "The delta times generated in the register were multplied by a factor of: " << SpeedFactor << endl
			<< endl
			<< "The following statistics has been made using the duration: " << FormatoReloj(TiempoOficial) << endl
			<< endl;

	// Calculamos los tiempos por espacio
	OpenSpace = ActividadDetalle(0, 0, TiempoOficial, registro, TiemposCont);
	CentralSpace = ActividadDetalle(1, 0, TiempoOficial, registro, TiemposCont);
	CloseSpace = ActividadDetalle(2, 0, TiempoOficial, registro, TiemposCont);
	// Calculamos las frecuencias
	OpenIn = FrecuenciaActividad(0, 0, TiempoOficial, registro, TiemposCont);
	CenterIn = FrecuenciaActividad(1, 0, TiempoOficial, registro, TiemposCont);
	CloseIn = FrecuenciaActividad(2, 0, TiempoOficial, registro, TiemposCont);

	double dOpenSpace = OpenSpace,
		   dCentralSpace = CentralSpace,
		   dCloseSpace = CloseSpace;

	archivo << "## Data for humans" << endl
			<< endl
			<< "Time spent on open spaces:   " << FormatoReloj(OpenSpace) << endl
			<< "Time spent on central space: " << FormatoReloj(CentralSpace) << endl
			<< "Time spent on closed spaces   " << FormatoReloj(CloseSpace) << endl
			<< "Entries to open spaces:      " << OpenIn << endl
			<< "Entries to central space:    " << CenterIn << endl
			<< "Entries to closed spaces:     " << CloseIn << endl
			<< endl
			<< "## Data for computers (seconds)" << endl
			<< endl
			<< dOpenSpace/1000 << endl
			<< dCentralSpace/1000 << endl
			<< dCloseSpace/1000 << endl
			<< OpenIn << endl
			<< CenterIn << endl
			<< CloseIn << endl
			<< endl;

	// Salto de tiempo (ms) entre eventos, para análisis detallados
	long long int PasoTiempo = 60000;

	// Tiempo en espacio abierto cada minuto
	archivo << "# Time spent on open spaces every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Duration of activity" << endl
			<< "----------------------------|----------------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << FormatoReloj(TiempoActivo) << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << TiempoActivo << endl;
	}
	archivo << endl;

	// Tiempo en espacio central cada minuto
	archivo << "# Time spent on central space every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Duration of activity" << endl
			<< "----------------------------|----------------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << FormatoReloj(TiempoActivo) << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << TiempoActivo << endl;
	}
	archivo << endl;

	// Tiempo en espacio cerrado cada minuto
	archivo << "# Time spent on closed spaces every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Duration of activity" << endl
			<< "----------------------------|----------------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << FormatoReloj(TiempoActivo) << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << TiempoActivo << endl;
	}
	archivo << endl;

	// Frecuencia de entradas a espacio abierto cada minuto
 	archivo << "# Entries to open spaces every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Entries" << endl
			<< "----------------------------|---------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		EpisodiosAct = FrecuenciaActividad(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << EpisodiosAct << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		EpisodiosAct = FrecuenciaActividad(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << EpisodiosAct << endl;
	}
	archivo << endl;

	// Frecuencia de entradas a espacio central cada minuto
 	archivo << "# Entries to central space every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Entries" << endl
			<< "----------------------------|---------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		EpisodiosAct = FrecuenciaActividad(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << EpisodiosAct << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		EpisodiosAct = FrecuenciaActividad(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << EpisodiosAct << endl;
	}
	archivo << endl;

	// Frecuencia de entradas a espacio cerrado cada minuto
 	archivo << "# Entries to closed spaces every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Entries" << endl
			<< "----------------------------|---------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		EpisodiosAct = FrecuenciaActividad(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << EpisodiosAct << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		EpisodiosAct = FrecuenciaActividad(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << EpisodiosAct << endl;
	}
	archivo << endl;

	// Mostramos los periodos como se registraron por el usuario
	long long int acum = 0;
	archivo << "# Full activity log" << endl
			<< endl
			<< "----------------------------------" << endl
			<< "|       Time       |    Space    |" << endl
			<< "----------------------------------" << endl;
	for (int d=0; d < TiemposCont; d++){
		archivo << "|   " << FormatoReloj(acum) << "   ";
		switch (registro[0][d]){
			case 0:
				archivo << "|    Open     |";
				break;
			case 1:
				archivo << "|    Central  |";
				break;
			case 2:
				archivo << "|    Closed   |";
				break;
		}
		archivo << endl;
		acum += registro[1][d];
	}
	archivo << "|   " << FormatoReloj(acum) << "   |    Finish   |   " << endl
			<< "----------------------------------" << endl;
	
	// Mostramos las entradas de tiempo originales
	archivo << endl
			<< "# Full delta log"
			<< endl;
	for (int i=0; i<TiemposCont; i++){
		archivo << registro[0][i] << " " << registro[1][i] << endl;
	}
	archivo << "-1" << endl;

	// Indicamos fin del reporte y versión con el que se realizó
	archivo << endl << endl << "> Report made with " << ATCRevision << " - rivel_co" << endl
			<< endl
			<< "End of the report" << endl;
	// Terminamos de escribir y cerramos nuestro archivo
	archivo.close();

	return;
}
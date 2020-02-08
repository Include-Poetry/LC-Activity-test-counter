// Función que guarda en un archivo los datos obtenidos del conteo
// 'ActLat' determina el tipo de actividad que nos interesa para latencia
void RegistrarDosEstados(int ActLat){
	AgregarComentario();
	AjustarVelocidad();
	// Creamos la variable que será nuestro archivo
	ofstream archivo;
	// Abrimos nuestro archivo, está listo para escribir en él
	archivo.open(RegNombre.c_str());

	// Calculamos el tiempo real de registro y se selecciona el oficial
	TiempoTotal = TiempoRealT1();
	TiempoOficial = min(TiempoTotal, TiempoRegis);

	// Obtenemos e imprimimos la cita
	string cite = citeFormat();
	archivo << endl << cite << endl << endl;

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

	// Se calculan todos los generales, desde el inicio hasta el final del tiempo oficial
 	TiempoActivo = ActividadDetalle(0, 0, TiempoOficial, registro, TiemposCont);
 	EpisodiosAct = FrecuenciaActividad(0, 0, TiempoOficial, registro, TiemposCont);
 	EpisodiosInact = FrecuenciaActividad(1, 0, TiempoOficial, registro, TiemposCont);
 	LatenciaAct = LatenciaActividad(ActLat, 0, TiempoOficial, registro, TiemposCont);
 	// Variables para mostrar los milisegundos en segundos
 	long double dTiempoActivo = TiempoActivo,
		   		dTiempoOficial = TiempoOficial,
		   		dLatenciaAct = LatenciaAct;

	// El título de actividad/inactividad varía según la actividad con la que inicie
	string LatTxt;
	if (ActLat){
		LatTxt = "Inactivity";
	} else {
		LatTxt = "Activity  ";
	}
 
 	// Se muestra el registro tal cual
	archivo	<< "# For the hole interval"<< endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "Activity duration:     " << FormatoReloj(TiempoActivo) << endl
			<< "Inactivity duration:   " << FormatoReloj(TiempoOficial-TiempoActivo) << endl
			<< LatTxt << " latency:     " << FormatoReloj(LatenciaAct) << endl
			<< "Activity episodes:     " << EpisodiosAct << endl
			<< "Inactivity episodes:   " << EpisodiosInact << endl
			<< endl
			<< "## Data for computers (seconds)" << endl
			<< endl
			<< dTiempoActivo/1000 << endl
			<< (dTiempoOficial-dTiempoActivo)/1000 << endl
			<< dLatenciaAct/1000 << endl
			<< EpisodiosAct << endl
			<< EpisodiosInact  << endl
			<< endl;

	// Salto de tiempo (ms) entre eventos, para análisis detallados
	long long int PasoTiempo;
	
	int bloques = 0;
	// Tiempo de actividad cada minuto
	PasoTiempo = 60000;
	archivo << "# Activity duration every minute" << endl
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
	bloques = TiempoOficial/PasoTiempo;
	if (bloques*PasoTiempo < TiempoOficial) bloques++;
	archivo << bloques << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << TiempoActivo << endl;
	}
	archivo << endl;

	// Tiempo de actividad cada 30 segundos
	PasoTiempo = 30000;
	archivo << "# Activity duration every 30 seconds" << endl
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
	bloques = TiempoOficial/PasoTiempo;
	if (bloques*PasoTiempo < TiempoOficial) bloques++;
	archivo << bloques << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		TiempoActivo = ActividadDetalle(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << TiempoActivo << endl;
	}
	archivo << endl;

	// Frecuencia de actividad cada minuto
	PasoTiempo = 60000;
 	archivo << "# Activity frequency every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Repetitions" << endl
			<< "----------------------------|-------------" << endl;
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

	// Frecuencia de actividad cada 30 segundos
	PasoTiempo = 30000;
	archivo << "# Activity frequency every 30 seconds" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Repetitions" << endl
			<< "----------------------------|-------------" << endl;
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
	
	// Mostramos los periodos como se registraron por el usuario
	long long int acum = 0;
	archivo << "# Full activity log" << endl
			<< endl
			<< "----------------------------------" << endl
			<< "|       Time       |  Activity   |" << endl
			<< "----------------------------------" << endl;
	for (int d=0; d < TiemposCont; d++){
		archivo << "|   " << FormatoReloj(acum) << "   ";
		switch (registro[0][d]){
			case 0:
				archivo << "|  Active     |" << endl;
				break;
			case 1:
				archivo << "|  Inactive   |" << endl;
				break;
		}
		acum += registro[1][d];
	}
	archivo << "|   " <<  FormatoReloj(acum) << "   |  Finish     |   " << endl
			<< "----------------------------------" << endl;

	// Mostramos las entradas de tiempo originales
	archivo << endl
			<< "# Full delta log" << endl
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
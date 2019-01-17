// Función que guarda en un archivo los datos obtenidos del conteo

void RegistrarTresyDosEstados(){
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

	CompactarActividad(registro);

	long long int TimeSA = ActividadDetalle(0, 0, TiempoOficial, registroMin, TiemposContMin),
				  TimeSB = ActividadDetalle(1, 0, TiempoOficial, registroMin, TiemposContMin),
				  TimeSC = ActividadDetalle(2, 0, TiempoOficial, registroMin, TiemposContMin),
				  TimeInte = ActividadDetalle(4, 0, TiempoOficial, registro, TiemposCont),
				  TimeGroo = ActividadDetalle(3, 0, TiempoOficial, registro, TiemposCont),
				  FrecSpaceA = FrecuenciaActividad(0, 0, TiempoOficial, registro, TiemposCont),
				  FrecSpaceB = FrecuenciaActividad(1, 0, TiempoOficial, registro, TiemposCont),
				  FrecSpaceC = FrecuenciaActividad(2, 0, TiempoOficial, registro, TiemposCont),
				  FrecInter = FrecuenciaActividad(4, 0, TiempoOficial, registro, TiemposCont),
				  FrecGroo = FrecuenciaActividad(3, 0, TiempoOficial, registro, TiemposCont),
				  LatencyInter = LatenciaActividad(4, 0, TiempoOficial, registro, TiemposCont),
				  LatencyGroo = LatenciaActividad(3, 0, TiempoOficial, registro, TiemposCont);

	double dTimeSA = TimeSA,
		   dTimeSB = TimeSB,
		   dTimeSC = TimeSC,
		   dTimeInte = TimeInte,
		   dTimeGroo = TimeGroo,
		   dLatencyInter = LatencyInter,
		   dLatencyGroo = LatencyGroo;

	// Mostramos un resumen de los datos
	archivo	<< "# For the hole interval"<< endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "Duration of interaction:    " << FormatoReloj(TimeInte) << endl
			<< "Frequency of interaction:    " << FrecInter << endl
			<< "Latency of interaction:     " << FormatoReloj(LatencyInter) << endl
			<< "Duration of grooming:      	" << FormatoReloj(TimeGroo) << endl
			<< "Frequency of grooming:       " << FrecGroo << endl
			<< "Latency of grooming:      	" << FormatoReloj(LatencyGroo) << endl
			<< "Time spent on " << TipoEspacioA << ": " << FormatoReloj(TimeSA) << endl
			<< "Time spent on " << TipoEspacioB << ": " << FormatoReloj(TimeSB) << endl
			<< "Time spent on " << TipoEspacioC << ": " << FormatoReloj(TimeSC) << endl
			<< "Entries to " << TipoEspacioA << ": " << FrecSpaceA << endl
			<< "Entries to " << TipoEspacioB << ": " << FrecSpaceB << endl
			<< "Entries to " << TipoEspacioC << ": " << FrecSpaceC << endl
			<< endl
			<< endl
			<< "## Data for computers (seconds)" << endl
			<< endl
			<< dTimeInte/1000  << endl
			<< FrecInter  << endl
			<< dLatencyInter/1000  << endl
			<< dTimeGroo/1000  << endl
			<< FrecGroo  << endl
			<< dLatencyGroo/1000  << endl
			<< dTimeSA/1000 << endl
			<< dTimeSB/1000 << endl
			<< dTimeSC/1000 << endl
			<< FrecSpaceA << endl
			<< FrecSpaceB << endl
			<< FrecSpaceC << endl;

	// Mostramos las entradas de tiempo originales
	archivo << endl
			<< "# Full delta log"
			<< endl;
	for (int i=0; i<TiemposCont; i++){
		archivo << registro[0][i] << " " << registro[1][i] << endl;
	}
	archivo << "-1" << endl;

	// Mostramos las entradas de tiempo originales
	archivo << endl
			<< "# Full compressed delta log"
			<< endl;
	for (int i=0; i<TiemposContMin; i++){
		archivo << registroMin[0][i] << " " << registroMin[1][i] << endl;
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

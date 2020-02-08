// Función que guarda en un archivo los datos obtenidos del conteo

void RegistrarTresEstadosNC(){
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

	// Contadores de duración
	long long int ObjectA, ObjectB, Grooming, Inactividad;
	// Contadores de frecuencia
	int ObjectAFrec, ObjectBFrec, GroomingFrec;

	// Se calculan todos los generales, desde el inicio hasta el fin del tiempo oficial
	ObjectA = ActividadDetalle(0, 0, TiempoOficial, registro, TiemposCont);
	ObjectB = ActividadDetalle(1, 0, TiempoOficial, registro, TiemposCont);
	Grooming = ActividadDetalle(2, 0, TiempoOficial, registro, TiemposCont);
	Inactividad = ActividadDetalle(3, 0, TiempoOficial, registro, TiemposCont);
	ObjectAFrec = FrecuenciaActividad(0, 0, TiempoOficial, registro, TiemposCont);
	ObjectBFrec = FrecuenciaActividad(1, 0, TiempoOficial, registro, TiemposCont);
	GroomingFrec = FrecuenciaActividad(2, 0, TiempoOficial, registro, TiemposCont);

	double dObjectA = ObjectA,
		   dGrooming = Grooming,
		   dObjectB = ObjectB,
		   dInactividad = Inactividad;

	// Mostramos un resumen de los datos
	archivo << "# For the hole interval" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "Interaction time with object " << TipoObjetoA << ":      " << FormatoReloj(ObjectA) << endl
			<< "Interaction time with object " << TipoObjetoB << ":     " << FormatoReloj(ObjectB) << endl
			<< "Grooming time:               " << FormatoReloj(Grooming) << endl
			<< "Inactivity time:             " << FormatoReloj(Inactividad) << endl
			<< "Interactions with object " << TipoObjetoA << ":     " << ObjectAFrec << endl
			<< "Interactions with object " << TipoObjetoB << ":     " << ObjectBFrec << endl
			<< "Frequency of grooming:      " << GroomingFrec << endl
			<< endl
			<< "# Data for computers (seconds)" << endl
			<< endl
			<< dObjectA/1000 << endl
			<< dObjectB/1000 << endl
			<< dGrooming/1000 << endl
			<< dInactividad/1000 << endl
			<< ObjectAFrec << endl
			<< ObjectBFrec << endl
			<< GroomingFrec << endl
			<< endl;
	
	// Salto de tiempo (ms) entre eventos, para análisis detallados
	long long int PasoTiempo;
	
	// Tiempo de interacción con el primer objeto cada minuto
	PasoTiempo = 60000;
	archivo << "# Duration of interaction with object " << TipoObjetoA << " every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Duration of interaction" << endl
			<< "----------------------------|-------------------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectA = ActividadDetalle(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << FormatoReloj(ObjectA) << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectA = ActividadDetalle(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << ObjectA << endl;
	}
	archivo << endl;

	// Tiempo de interacción con el segundo objeto cada minuto
	archivo << "# Duration of interaction with object " << TipoObjetoB << " every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Duration of interaction" << endl
			<< "----------------------------|-------------------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectB = ActividadDetalle(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << FormatoReloj(ObjectB) << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectB = ActividadDetalle(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << ObjectB << endl;
	}
	archivo << endl;

	// Tiempo de grooming cada minuto
	archivo << "# Duration of grooming every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Duration of grooming" << endl
			<< "----------------------------|----------------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		Grooming = ActividadDetalle(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << FormatoReloj(Grooming) << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		Grooming = ActividadDetalle(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << Grooming << endl;
	}
	archivo << endl;

	// Frecuencia de interacción con el primer objeto cada minuto
	archivo << "# Frequency of interaction with object " << TipoObjetoA << " every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Repetitions" << endl
			<< "----------------------------|-------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectAFrec = FrecuenciaActividad(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << ObjectAFrec << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectAFrec = FrecuenciaActividad(0, d, d+PasoTiempo, registro, TiemposCont);
		archivo << ObjectAFrec << endl;
	}
	archivo << endl;

	// Frecuencia de interacción con el segundo objeto cada minuto
	archivo << "# Frequency of interaction with object " << TipoObjetoB << " every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Repetitions" << endl
			<< "----------------------------|-------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectBFrec = FrecuenciaActividad(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << ObjectBFrec << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		ObjectBFrec = FrecuenciaActividad(1, d, d+PasoTiempo, registro, TiemposCont);
		archivo << ObjectBFrec << endl;
	}
	archivo << endl;

	// Frecuencia de grooming cada minuto
	archivo << "# Frequency of grooming every minute" << endl
			<< endl
			<< "## Data for humans" << endl
			<< endl
			<< "            Lapse           | Repetitions" << endl
			<< "----------------------------|-------------" << endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		GroomingFrec = FrecuenciaActividad(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << FormatoReloj(d) << " - " << FormatoReloj(d+PasoTiempo) 
				<< " | " << GroomingFrec << endl;
	}
	archivo << endl 
			<< "## Data for computers (ms)" << endl
			<< endl;
	for (int d=0; d < TiempoOficial; d+=PasoTiempo){
		GroomingFrec = FrecuenciaActividad(2, d, d+PasoTiempo, registro, TiemposCont);
		archivo << GroomingFrec << endl;
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
				archivo << "|   Objet A   |" << endl;
				break;
			case 1:
				archivo << "|   Objet B   |" << endl;
				break;
			case 2:
				archivo << "|   Grooming  |" << endl;
				break;
			case 3:
				archivo << "|   Inactive  |" << endl;
				break;
		}
		acum += registro[1][d];
	}
	archivo << "|   " << FormatoReloj(acum) << "   |   Finish    |" << endl
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
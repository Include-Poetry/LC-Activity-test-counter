// Función que guarda en un archivo los datos obtenidos del conteo

void RegistrarDosEstados(){
	// Creamos la variable que será nuestro archivo
	ofstream archivo;
	// Abrimos nuestro archivo, está listo para escribir en él
	archivo.open(RegNombre);
	
	TiempoTotal = 0;
	for (int j=0; j < TiemposCont; j++){
		TiempoTotal += tiempos[j];
	}
	TiempoOficial = min(TiempoTotal, TiempoRegis);

	// Mostramos un resumen de los datos
	archivo << "Animal ID: " << NombreControl << endl
			<< "Prueba realizada: " << TipoExperimento << " -> " << TExpCompleto << endl
			<< "Fecha del experimento: " << ExpDia << "-" << ExpMes << "-" << ExpAno << endl << endl
			
			<< "Tiempo especificado por el usuario: " << FormatoReloj(TiempoRegis) << endl
			<< "Tiempo total registrado: " << FormatoReloj(TiempoTotal) << endl << endl
			
			<< "Las siguientes estadísticas se evaluaron en base al tiempo: " << FormatoReloj(TiempoOficial) << endl << endl;

	double pcActivo = PorcentajeActividad(0, TiempoOficial);
	double pcInactivo = 100 - pcActivo;
	archivo	<< "Para todo el intervalo usado:"<< endl
			<< "Tiempo de actividad: " << FormatoReloj(TiempoActivo) << endl
			<< "Tiempo de inactividad: " << FormatoReloj(TiempoOficial-TiempoActivo) << endl
			<< "Porcentaje de actividad: " << pcActivo << " %" << endl
			<< "Porcentaje de inactividad: " << pcInactivo << " %" << endl
			<< "Tiempo a primera inactividad: " << FormatoReloj(tPrimero) << endl
			<< "Mayor periodo de actividad: " << FormatoReloj(MayAct) << endl
			<< "Mayor periodo de inactividad: " << FormatoReloj(MayInact) << endl << endl;
	
	pcActivo = PorcentajeActividad(TiempoOficial/3, 2*TiempoOficial/3);
	pcInactivo = 100 - pcActivo;
	archivo << "Para los últimos 2/3 del intervalo usado:" << endl
			<< "Tiempo de actividad: " << FormatoReloj(TiempoActivo) << endl
			<< "Tiempo de inactividad: " << FormatoReloj((2*TiempoOficial/3)-TiempoActivo) << endl
			<< "Porcentaje de actividad: " << pcActivo << " %" << endl
			<< "Porcentaje de inactividad: " << pcInactivo << " %" << endl
			<< "Tiempo a primera inactividad: " << FormatoReloj(tPrimero) << endl
			<< "Mayor periodo de actividad: " << FormatoReloj(MayAct) << endl
			<< "Mayor periodo de inactividad: " << FormatoReloj(MayInact) << endl << endl;
	
	pcActivo = PorcentajeActividad(TiempoOficial/6, 4*TiempoOficial/6);
	pcInactivo = 100 - pcActivo;
	archivo << "Para los 4/6 intermedios del intervalo usado:" << endl
			<< "Tiempo de actividad: " << FormatoReloj(TiempoActivo) << endl
			<< "Tiempo de inactividad: " << FormatoReloj((4*TiempoOficial/6)-TiempoActivo) << endl
			<< "Porcentaje de actividad: " << pcActivo << " %" << endl
			<< "Porcentaje de inactividad: " << pcInactivo << " %" << endl
			<< "Tiempo a primera inactividad: " << FormatoReloj(tPrimero) << endl
			<< "Mayor periodo de actividad: " << FormatoReloj(MayAct) << endl
			<< "Mayor periodo de inactividad: " << FormatoReloj(MayInact) << endl << endl;

	// Mostramos los periodos como se registraron por el usuario
	archivo << "Reporte completo de periodos actividad/inactividad" << endl
			<< "respecto al inicio del registro:" << endl;
	int hora = 0, minuto = 0, segundo = 0, milesima = 0;
	int actual;
	archivo << "-----------------------------------------------------------" << endl
			<< "|     Inicio actividad       |     Inicio inactividad     |" << endl
			<< "-----------------------------------------------------------" << endl;
	long long int acum = 0;
	for (int i=0; i<TiemposCont; i++){
		actual = tiempos[i]; 			// Conversión a entero
		acum += actual;
		// Escribimos la información que se solicita
		archivo << "|     " << FormatoReloj(acum) << "           ";
		// Formato estilo tabla
		if (i%2 == 1)	archivo << "|\n";
	}
	
	// Mostramos las entradas de tiempo originales
	archivo << endl << endl << "Registro completo de deltas de tiempo (ms):" << endl;
	for (int i=0; i<TiemposCont; i++){
		archivo << tiempos[i] << endl;
	}
	archivo << endl << endl << "Registro realizado con " << ATCRevision << " - rivel_co" << endl
			<< "Fin del reporte" << endl;
	// Terminamos de escribir y cerramos nuestro archivo
	archivo.close();

	return;
}
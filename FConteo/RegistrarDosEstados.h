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

	double dTiempoActivo = TiempoActivo,
		   dTiempoOficial = TiempoOficial,
		   dtPrimero = tPrimero,
		   dMayAct = MayAct,
		   dMayInact = MayInact,
		   dPromAct = PromAct,
		   dPromInact = PromInact;

	// Mostramos un resumen de los datos
	archivo << "Animal ID: " << NombreControl << endl
			<< "Prueba realizada: " << TipoExperimento << " -> " << TExpCompleto << endl
			<< "Fecha del experimento: " << ExpDia << "-" << ExpMes << "-" << ExpAno << endl << endl
			
			<< "Tiempo especificado por el usuario: " << FormatoReloj(TiempoRegis) << endl
			<< "Tiempo total registrado: " << FormatoReloj(TiempoTotal) << endl << endl
			
			<< "Las siguientes estadísticas se evaluaron en base al tiempo: " << FormatoReloj(TiempoOficial) << endl << endl;

	double pcActivo = PorcentajeActividad(0, TiempoOficial);
	double pcInactivo = 100 - pcActivo;
	dTiempoActivo = TiempoActivo, dTiempoOficial = TiempoOficial, dtPrimero = tPrimero, 
	dMayAct = MayAct, dMayInact = MayInact, dPromAct = PromAct, dPromInact = PromInact;
	archivo	<< "Para todo el intervalo usado"<< endl
			<< endl
			<< "- Datos para humanos" << endl
			<< "Tiempo de actividad:             " << FormatoReloj(TiempoActivo) << endl
			<< "Tiempo de inactividad:           " << FormatoReloj(TiempoOficial-TiempoActivo) << endl
			<< "Porcentaje de actividad:         " << pcActivo << " %" << endl
			<< "Porcentaje de inactividad:       " << pcInactivo << " %" << endl
			<< "Tiempo a primera inactividad:    " << FormatoReloj(tPrimero) << endl
			<< "Mayor periodo de actividad:      " << FormatoReloj(MayAct) << endl
			<< "Mayor periodo de inactividad:    " << FormatoReloj(MayInact) << endl
			<< "Promedio de fase de actividad:   " << FormatoReloj(PromAct) << endl
			<< "Promedio de fase de inactividad: " << FormatoReloj(PromInact) << endl
			<< "Episodios de actividad:   		 " << EpisodiosAct << endl
			<< "Episodios de inactividad: 		 " << EpisodiosInact << endl
			<< endl
			<< "+ Datos para computadoras (en segundos):" << endl
			<< dTiempoActivo/1000 << endl
			<< (dTiempoOficial-dTiempoActivo)/1000 << endl
			<< pcActivo << endl
			<< pcInactivo << endl
			<< dtPrimero/1000 << endl
			<< dMayAct/1000 << endl
			<< dMayInact/1000 << endl
			<< dPromAct/1000 << endl
			<< dPromInact/1000 << endl
			<< EpisodiosAct << endl
			<< EpisodiosInact  << endl
			<< endl;

	long long int TiempoMinutoResto = TiempoOficial%60000,
				  TiempoMinutos = TiempoOficial;
	archivo << "Porcentaje de actividad por cada minuto" << endl
			<< endl
			<< "- Datos para humanos" << endl
			<< "Del minuto   al     minuto  | Actividad (porcentaje)" << endl;
	for (int i=0; i<TiempoMinutos; i+=60000){
		if (TiempoMinutoResto && i+60000 >= TiempoMinutos){
			pcActivo = PorcentajeActividad(i, TiempoMinutoResto);
		} else {
			pcActivo = PorcentajeActividad(i, 60000);
		}
		archivo << FormatoReloj(i) << " - " << FormatoReloj(i+60000) << " | " << pcActivo << endl;
	}
	archivo << endl << "+ Datos para computadoras (porcentaje):" << endl;
	if (TiempoMinutoResto){
		archivo << (TiempoMinutos/60000) + 1 << endl;
	} else {
		archivo << TiempoMinutos/60000 << endl;
	}
	for (int i=0; i<TiempoMinutos; i+=60000){
		if (TiempoMinutoResto && i+60000 >= TiempoMinutos){
			pcActivo = PorcentajeActividad(i, TiempoMinutoResto);
		} else {
			pcActivo = PorcentajeActividad(i, 60000);
		}
		archivo << pcActivo << endl;
	}
	archivo << endl;

	archivo << "Tiempo de actividad por cada minuto" << endl
			<< endl
			<< "- Datos para humanos" << endl
			<< "Del minuto   al     minuto  | Actividad (tiempo)" << endl;
	for (int i=0; i<TiempoMinutos; i+=60000){
		if (TiempoMinutoResto && i+60000 >= TiempoMinutos){
			pcActivo = PorcentajeActividad(i, TiempoMinutoResto);
		} else {
			pcActivo = PorcentajeActividad(i, 60000);
		}
		archivo << FormatoReloj(i) << " - " << FormatoReloj(i+60000) << " | " << FormatoReloj(TiempoActivo) << endl;
	}
	archivo << endl << "+ Datos para computadoras (milisegundos):" << endl;
	if (TiempoMinutoResto){
		archivo << (TiempoMinutos/60000) + 1 << endl;
	} else {
		archivo << TiempoMinutos/60000 << endl;
	}
	for (int i=0; i<TiempoMinutos; i+=60000){
		if (TiempoMinutoResto && i+60000 >= TiempoMinutos){
			pcActivo = PorcentajeActividad(i, TiempoMinutoResto);
		} else {
			pcActivo = PorcentajeActividad(i, 60000);
		}
		archivo << TiempoActivo << endl;
	}
	archivo << endl;
	/*
	pcActivo = PorcentajeActividad(TiempoOficial/6, 4*TiempoOficial/6);
	pcInactivo = 100 - pcActivo;
	dTiempoActivo = TiempoActivo, dTiempoOficial = TiempoOficial, dtPrimero = tPrimero, 
	dMayAct = MayAct, dMayInact = MayInact, dPromAct = PromAct, dPromInact = PromInact;
	archivo << "Para los 4/6 intermedios del intervalo usado:" << endl
			<< endl
			<< "- Datos para humanos" << endl
			<< "Tiempo de actividad:             " << FormatoReloj(TiempoActivo) << endl
			<< "Tiempo de inactividad:           " << FormatoReloj((4*TiempoOficial/6)-TiempoActivo) << endl
			<< "Porcentaje de actividad:         " << pcActivo << " %" << endl
			<< "Porcentaje de inactividad:       " << pcInactivo << " %" << endl
			<< "Tiempo a primera inactividad:    " << FormatoReloj(tPrimero) << endl
			<< "Mayor periodo de actividad:      " << FormatoReloj(MayAct) << endl
			<< "Mayor periodo de inactividad:    " << FormatoReloj(MayInact) << endl
			<< "Promedio de fase de actividad:   " << FormatoReloj(PromAct) << endl
			<< "Promedio de fase de inactividad: " << FormatoReloj(PromInact) << endl
			<< "Episodios de actividad:   		 " << EpisodiosAct << endl
			<< "Episodios de inactividad: 		 " << EpisodiosInact << endl
			<< endl
			<< "+ Datos para computadoras (en segundos):" << endl
			<< dTiempoActivo/1000 << endl
			<< ((4*dTiempoOficial/6)-dTiempoActivo)/1000 << endl
			<< pcActivo << endl
			<< pcInactivo << endl
			<< dtPrimero/1000 << endl
			<< dMayAct/1000 << endl
			<< dMayInact/1000 << endl
			<< dPromAct/1000 << endl
			<< dPromInact/1000 << endl
			<< EpisodiosAct << endl
			<< EpisodiosInact  << endl
			<< endl;

	pcActivo = PorcentajeActividad(TiempoOficial/3, 2*TiempoOficial/3);
	pcInactivo = 100 - pcActivo;
	dTiempoActivo = TiempoActivo, dTiempoOficial = TiempoOficial, dtPrimero = tPrimero,
	dMayAct = MayAct, dMayInact = MayInact, dPromAct = PromAct, dPromInact = PromInact;
	archivo << "Para los últimos 2/3 del intervalo usado:" << endl
			<< endl
			<< "- Datos para humanos" << endl
			<< "Tiempo de actividad:             " << FormatoReloj(TiempoActivo) << endl
			<< "Tiempo de inactividad:           " << FormatoReloj((2*TiempoOficial/3)-TiempoActivo) << endl
			<< "Porcentaje de actividad:         " << pcActivo << " %" << endl
			<< "Porcentaje de inactividad:       " << pcInactivo << " %" << endl
			<< "Tiempo a primera inactividad:    " << FormatoReloj(tPrimero) << endl
			<< "Mayor periodo de actividad:      " << FormatoReloj(MayAct) << endl
			<< "Mayor periodo de inactividad:    " << FormatoReloj(MayInact) << endl
			<< "Promedio de fase de actividad:   " << FormatoReloj(PromAct) << endl
			<< "Promedio de fase de inactividad: " << FormatoReloj(PromInact) << endl
			<< "Episodios de actividad:   		 " << EpisodiosAct << endl
			<< "Episodios de inactividad: 		 " << EpisodiosInact << endl
			<< endl
			<< "+ Datos para computadoras (en segundos):" << endl
			<< dTiempoActivo/1000 << endl
			<< ((2*dTiempoOficial/3)-dTiempoActivo)/1000 << endl
			<< pcActivo << endl
			<< pcInactivo << endl
			<< dtPrimero/1000 << endl
			<< dMayAct/1000 << endl
			<< dMayInact/1000 << endl
			<< dPromAct/1000 << endl
			<< dPromInact/1000 << endl
			<< EpisodiosAct << endl
			<< EpisodiosInact  << endl
			<< endl;
	*/
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
	archivo << "-1" << endl;

	archivo << endl << endl << "Registro realizado con " << ATCRevision << " - rivel_co" << endl
			<< "Fin del reporte" << endl;
	// Terminamos de escribir y cerramos nuestro archivo
	archivo.close();

	return;
}
// Calculamos el porcentaje de tiempo de actividad

double PorcentajeActividad(long long int c, long long int f){
	long long int inicio = c,
				  fin = f;
	long long int actual;
	TiempoActivo = 0;
	int cont = 0, cont2 = 0;
	MayAct = MayInact = 0;
	tPrimero = 0;

	int i = 0;

	long long int acum = 0;
	long long int resto, extra;

	while (acum < inicio){
		acum += tiempos[i++];
	}
	resto = acum - inicio;
	if ((i-1)%2){
		TiempoActivo += resto;
		if (tiempos[i] == 0) tPrimero = tiempos[i+1];
		else tPrimero = resto;
		if (resto > f){
			MayAct = f;
		} else MayAct = resto;
		cont++;
	} else {
		if (resto > f){
			MayInact = f;
		} else MayInact = resto;
		cont2++;
	}
	inicio = i;

	acum = resto;
	while (acum < fin){
		acum += tiempos[i++];
	}
	extra = acum - fin;
	if ((i-1)%2){
		TiempoActivo -= extra;
	}
	fin = i;

	for (i=inicio; i < fin; i++){
		actual = tiempos[i];
		if (i%2){
			TiempoActivo += actual;
			cont++;
			if (i+1 == fin) actual -= extra;
			if (actual > MayAct) MayAct = actual;
		} else {
			cont2++;
			if (i+1 == fin) actual -= extra;
			if (actual > MayInact) MayInact = actual;
		}
	}
	//if (MayAct > f) MayAct -= resto;

	if (tPrimero > f) tPrimero = f;

	double arriba = TiempoActivo, abajo = f;
	double final = (arriba/abajo)*100;
	
	PromAct = TiempoActivo/cont;
	if (cont2 == 0){
		PromInact = 0;
	} else {
		PromInact = (f-TiempoActivo)/(cont2);
	}
	
	return final;
}
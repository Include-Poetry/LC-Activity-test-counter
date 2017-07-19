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
	// Contamos hasta alcanzar el punto de inicio
	while (acum < inicio){
		acum += tiempos[i++];
	}
	// 10
	// 0 2 3 4 1
	// Corregimos el tiempo eliminando lo que no entra en el inicio
	resto = acum - inicio;

	if ((i-1)%2){	// Si el último en sumar fue par
		if (resto){
			cont++;
		}
		TiempoActivo += resto;
		if (tiempos[i] == 0) tPrimero = tiempos[i+1];
		else tPrimero = resto;
		if (resto > f){
			MayAct = f;
		} else MayAct = resto;
	} else {
		if (resto){
			cont2++;
		}
		if (resto > f){
			MayInact = f;
		} else MayInact = resto;
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
	if (tPrimero > f) tPrimero = f;

	double arriba = TiempoActivo, abajo = f;
	double final = (arriba/abajo)*100;
	
	EpisodiosAct = cont;
	EpisodiosInact = cont2-1;

	if (EpisodiosAct == 0){
		PromAct = 0;
	} else {
		PromAct = TiempoActivo/EpisodiosAct;
	}
	if (EpisodiosInact == 0){
		PromInact = 0;
	} else {
		PromInact = (f-TiempoActivo)/(EpisodiosInact);
	}
	
	
	return final;
}
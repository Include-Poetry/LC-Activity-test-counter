// Calculamos el porcentaje de tiempo de actividad

double PorcentajeActividad(){
	long long int actual;
	TiempoActivo = TiempoTotal = 0;
	int cont = 0, cont2 = 0;
	MayAct = MayInact = 0;
	DeltasVal = -1;

	for (int i=0; i<TiemposCont; i++){
		actual = tiempos[i];
		TiempoTotal += actual;
		
		actual = TiempoTotal >= TiempoRegis ? TiempoRegis - (TiempoTotal - actual) : tiempos[i];
		
		if (DeltasVal == -1){
			if (i%2){
				TiempoActivo += actual;
				cont++;
				if (actual > MayAct) MayAct = actual;
			} else {
				cont2++;
				if (actual > MayInact) MayInact = actual;
			}
		}
		if (DeltasVal == -1 && actual != tiempos[i]){
			DeltasVal = i;
		}
	}
	TiempoOficial = min(TiempoTotal, TiempoRegis);
	double arriba = TiempoActivo, abajo = TiempoOficial;
	double final = (arriba/abajo)*100;
	
	PromAct = TiempoActivo/cont;
	if (cont2 - 1 == 0){
		PromInact = 0;
	} else {
		PromInact = (TiempoOficial-TiempoActivo)/(cont2 - 1);
	}
	
	return final;
}
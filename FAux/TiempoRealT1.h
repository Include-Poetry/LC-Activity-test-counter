// Esta función devuelve el tiempo total registrado, sin discriminar
// entre tipos de actividad (no se use para TCS por ejemplo)
long long int TiempoRealT1(){
	long long int final = 0;
	for (int j=0; j < TiemposCont; j++){
		final += registro[1][j];
	}
	return final;
}
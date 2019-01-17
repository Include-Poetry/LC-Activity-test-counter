// act -> número que dice qué actividad se busca
// ini -> número grande que dice el milisegundo del que se va a empezar
// fin -> número grande que dice el milisegundo en el que terminará
// evaluando -> el arreglo que contiene los datos a procesar
// RegSize -> Tamaño del arreglo que está procesando
// La función regresa en milisegundos el tiempo de latencia de 'ini' a 'fin' de la actividad 'act'
long long int LatenciaActividad(int act, long long int ini, long long int fin, long long int evaluando[2][MAX], int RegSize){
	if (fin < ini){	// Evaluación para evitar errores
		return -1;
	}
	// Acumulador hasta llegar al tiempo deseado
	long long int aux = 0;
	int i;
	for (i=0; aux < ini && i < RegSize; i++){
		aux += evaluando[1][i];
	}
	// Quitamos la diferencia (por lo que nos pasamos en la actividad actual)
	aux -= ini;
	// Declaramos la variable que sumará sólo de lo que nos interesa
	long long int final = 0;
	// Cargamos la cantidad que llevamos si es que aplica
	int temp = i > 0 ? evaluando[0][i-1] : evaluando[0][i];
	if (temp != act){
		final += aux;
	} else if (aux > 0) {
		// Este if es por si no caímos exactamente en el fin-inicio de un estado
		// De no haber caído exacto, solo se devuelve el 0, porque estamos dentro del
		// peroiodo buscado
		return 0;
	}
	// Reinicializamos a aux para que ahora vaya sumando hasta llegar al milisegundo final
	aux = ini + aux;
	// Recorremos los registros hasta terminar
	for (; aux < fin && i < RegSize; i++){
		// Sólo agregamos los diferentes al estado buscado
		if (evaluando[0][i] != act){
			final += evaluando[1][i];
		} else {
			// En el estado buscado hacemos break pues ya terminamos
			break;
		}
		aux += evaluando[1][i];
	}
	// Cuando hemos terminado descontamos lo necesario en caso de habernos pasado
	temp = i > 0 ? evaluando[0][i-1] : evaluando[0][i];
	if (temp != act && aux > fin){
		final -= aux-fin;
	}
	// Regresamos la respuesta final
	return final;
}
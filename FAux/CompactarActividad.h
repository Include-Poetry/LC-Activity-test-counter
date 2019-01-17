// Esta función compacta los eventos pequeños que ocurren simultáneamente en eventos mayores
// por ejemplo que haga grooming a la vez que está en determinado espacio.
// original -> El arreglo del que está comprimiendo, el base
void CompactarActividad(long long int original[2][MAX]){
	int it = 0;

	for (int j=0; j<100000; j++){
		registroMin[0][j] = 0;
		registroMin[1][j] = 0;
	}

	for (int i=0; i<TiemposCont; ){
		if (original[0][i] == 0){
			while (original[0][i] != 1 && original[0][i] != 2 && i < TiemposCont){
				registroMin[1][it] += original[1][i];
				i++;
			}
			registroMin[0][it] = 0;
			it++;
		}
		if (original[0][i] == 1){
			while (original[0][i] != 0 && original[0][i] != 2 && i < TiemposCont){
				registroMin[1][it] += original[1][i];
				i++;
			}
			registroMin[0][it] = 1;
			it++;
		}
		if (original[0][i] == 2){
			while (original[0][i] != 0 && original[0][i] != 1 && i < TiemposCont){
				registroMin[1][it] += original[1][i];
				i++;
			}
			registroMin[0][it] = 2;
			it++;
		}
	}
	
	TiemposContMin = it;
	return;
}
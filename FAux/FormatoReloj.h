string FormatoReloj(long long int t){
	// Recibe el tiempo en milisegundos como entero y lo convierte en cadena con formato reloj
	int horas, minutos, segundos, mili;
	mili = t%1000;
	t /= 1000;
	segundos = t%60;
	t /= 60;
	minutos = t%60;
	t /= 60;
	horas = t;

	string final = Formato(horas, 2) + ':' + Formato(minutos, 2) + ':' + Formato(segundos, 2) + ':' + Formato(mili, 3);
	return final;
}
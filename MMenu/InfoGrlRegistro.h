// Muestra la información general del registro actual

void InfoGrlRegistro(){
	cout << "    El archivo se guardar\240 en la ubicaci\242n: " << endl
		 << "       " << RutaRegistro << RegNombre << endl
		 << endl 
		 << "    La prueba a registrar es: " << TipoExperimento << endl
		 << "    identificada como: " << TExpCompleto << endl
		 << endl
		 << "    La prueba se ajustar\240 a: " << FormatoReloj(TiempoRegis) << endl
		 << endl;
}
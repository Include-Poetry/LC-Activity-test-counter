// Muestra la información general del registro actual

void InfoGrlRegistro(){
	cout << "    The file will be saved in the following location: " << endl
		 << "       " << RutaRegistro << RegNombre << endl
		 << endl 
		 << "    The test that will be registered is: " << TipoExperimento << endl
		 << "    identified as: " << TExpCompleto << endl
		 << endl
		 << "    The duration of the test is: " << FormatoReloj(TiempoRegis) << endl
		 << endl;
}
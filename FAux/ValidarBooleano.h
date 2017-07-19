// Función que valida una entrada de respuesta a Sí (S/s) o No (N/n)

bool ValidarBooleano(){
	string ans;

	while (true){
		cin >> ans;

		if (ans == "S" || ans == "s"){	// Repuesta positiva (Sí)
			cout << endl;
			return true;
		}
		if (ans == "N" || ans == "n"){ // Respuesta negativa (No)
			cout << endl;
			return false;
		}
		// Otras respuestas no válidas
		cout << endl 
			 << "    Ingresa 'S' o 's' para indicar 'S\241' " << endl
			 << "    Ingresa 'N' o 'n' para indicar 'No'" << endl
			 << "    Tu respuesta: ";
	}
}
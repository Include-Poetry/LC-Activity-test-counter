// Función que valida una entrada de respuesta a Sí (S/s) o No (N/n)

bool ValidarBooleano(char Yes, char Nop){
	char ans;
	while (true){
		cin >> ans;

		// Convertir minúsculas a mayúsculas
		if (ans > 96 && ans < 123){
			ans -= 32;
		}
		// TODO: Remover esto o reactivarlo si voy a usar string
		// Las minúsculas se hacen mayúsculas
		/*
		for (int i=0; i<ans.size(); i++){
			if (ans[i] > 96 && ans[i] < 123){
				ans[i] -= 32;
			}
		}*/
		cout << endl;
		if (ans == Yes) return true;	// Repuesta positiva (Sí)
		if (ans == Nop) return false;// Respuesta negativa (No)
		// Otras respuestas no válidas
		cout << "    Type only " << Yes << " or " << Nop << " to indicate one of the options above"<< endl
			 << "    Your answer: ";
	}
}
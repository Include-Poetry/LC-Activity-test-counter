// Para dar formato a los numeros tipo reloj

// Recibe dos parámetro enteros x, n
// x -> Número que se va a formatear
// n -> Cantidad de espacios a rellenar

// Devuelve una cadena del formato (0n - 1) + x
// Ej: x = 3, n = 2, return 03

string Formato(int x, int n){
	stringstream ss;
	ss << setw(n) << setfill('0') << x;
	string s = ss.str();
	return s;
}
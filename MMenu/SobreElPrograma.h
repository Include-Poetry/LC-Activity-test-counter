// Información sobre el programa

void SobreElPrograma(){
	Cabecera("Sobre la funci\242n del programa");

	cout << "    Este es un sumario de las caracter\241sticas del programa." << endl
		 << "    Una descripci\242n completa se puede encontrar en:" << endl
		 << "    -  https://github.com/Include-Poetry/LC-Activity-test-counter" << endl
		 << endl
		 << endl
		 << "    El programa eval\243a distintas estad\241sticas sobre el tiempo de" << endl
		 << "    actividad e inactividad de un animal experimental en distintas pruebas" << endl
		 << "    de conducta. La versi\242n actual est\240 especialmente enfocada para" << endl
		 << "        TST - Tail Suspension Test" << endl
		 << "        FST - Forced Swim Test" << endl
		 << "        PM  - Plus Maze" << endl
		 << "    aunque el m\202todo de funcionamiento puede aplicarse tambi\202n a" << endl
		 << "    otras pruebas que eval\243en dos o tres estados distintos."
		 << endl
		 << endl
		 << "            Sobre el m\202todo de funcionamiento en conteo est\240ndar" << endl
		 << endl
		 << "    Para la utilizaci\242n del programa se debe estar observando la prueba" << endl
		 << "    al mismo momento en que se ejecuta el conteo." << endl
		 << "    Una vez que la prueba comienza, el usuario deber\240 pulsar una tecla" << endl
		 << "    cada que el animal cambia de estado o posici\242n." << endl
		 << "    El programa mide el tiempo que dura el animal en cada estado/posici\242n" << endl
		 << "    y en base a ello realiza el an\240lisis." 
		 << endl
		 << endl
		 << "                         Sobre las pruebas identificadas" << endl
		 << endl
		 << "    El programa identifica y se optimiza para tres distintas pruebas:" << endl
		 << "    - TST -> Tail suspension test" << endl
		 << "    - FST -> Forced swim test" << endl
		 << "    - PM  -> Plus maze" << endl
		 << "    En las primeras dos pruebas se eval\243an dos posibles estados, que son:" << endl
		 << "    - Actividad / Inactividad" << endl
		 << "    Adem\240s se da por hecho que el sujeto de prueba comienza con un estado" << endl
		 << "    de actividad." << endl
		 << "    Para la tercer prueba se eval\243an tres posibles ubicaciones:" << endl
		 << "    - Espacio abierto / Espacio cerrado / Espacio central" << endl
		 << "    Para una prueba no identificada se realiza un an\240lisis de dos estados." << endl
		 << "    Para que el programa identifique correctamente la prueba, debe ser escrita" << endl
		 << "    tal y como se ha escrito el acr\242nimo anteriormente citado."
		 << endl
		 << endl
		 << "                       Sobre las estad\241sticas evaluadas" << endl
		 << endl
		 << "    Las estad\241sticas que se realizan en base a los tiempos de cambio y " << endl 
		 << "    seg\243n aplique son:" << endl
		 << "    - Tiempo total registrado" << endl
		 << "    - Tiempo de evaluaci\242n determinado por el usuario" << endl
		 << "    - Tiempo total de actividad" << endl
		 << "    - Tiempo total de inactividad" << endl
		 << "    - Tiempo total en cada posici\242n" << endl
		 << "    - Porcentaje de tiempo de actividad" << endl
		 << "    - Porcentaje de tiempo de inactividad" << endl
		 << "    - Porcentaje del tiempo en cada posici\242n" << endl
		 << "    - Tiempo de latencia (a primera inactividad)" << endl
		 << "    - Mayor periodo de actividad" << endl
		 << "    - Mayor periodo de inactividad" << endl
		 << "    - Promedio de fase de actividad" << endl
		 << "    - Promedio de fase de inactividad" << endl
		 << "    - Cantidad de episodios de actividad" << endl
		 << "    - Cantidad de episodios de inactividad" << endl
		 << "    - Cantidad de entradas en cada espacio" << endl
		 << "    De forma adicional se agrega un reporte completo de:" << endl
		 << "    - Registro minuto a minuto de porcentaje de actividad" << endl
		 << "    - Registro minuto a minuto de tiempo de actividad" << endl
		 << "    - Tiempo de cambio de estado respecto a la duraci\242n total del registro" << endl
		 << "    - Registro de deltas de tiempo (tiempo transcurrido en ms entre cada" << endl
		 << "      cambio de estado)." << endl
		 << endl
		 << endl
		 << "                        Sobre los archivos de registro" << endl
		 << endl
		 << "    Al finalizar cada registro los archivos se guardan en una ruta como:" << endl
		 << "       Registros/[Nombre de la prueba]/[Fecha del experimento]/" << endl
		 << "    a partir de la ruta en donde se ejecut\242 en programa y en archivo:" << endl
		 << "       [Fecha del experimento] [Nombre de la prueba] [ID del animal].txt" << endl
		 << endl
		 << endl
		 << "    Este programa es de c\242digo abierto, si quieres contribuir a mejorar" << endl
		 << "    esta herramienta agregando nuevas funciones haz fork en:" << endl
		 << "    -  https://github.com/Include-Poetry/LC-Activity-test-counter" << endl
		 << "    Si encuentras alg\243n problema en el funcionamiento o quieres hacer" << endl
		 << "    alguna sugerencia, entra a:" << endl
		 << "    -  https://github.com/Include-Poetry/LC-Activity-test-counter/issues" << endl
		 << "    Descarga la \243ltima versi\242n del programa en:" << endl
		 << "    -  https://github.com/Include-Poetry/LC-Activity-test-counter/releases" << endl
		 << endl
		 << endl
		 << endl
		 << "    Desarrollado por Ricardo Vel\240zquez Contreras - rivel_co" << endl
		 << endl
		 << endl
		 << "    Presiona cualquier tecla para volver...";

	system("pause>>null");
	return;
}
# Activity test counter

## Descripción

Este programa es un auxiliar en el análisis y registro de pruebas de conducta. Permite generar estadísticas del experimento con precisión de milésimas de segundo, de forma sencilla y al mismo tiempo en que se observa la prueba o grabación de la misma. Especialmente optimizado para las pruebas:

- [Tail suspension test](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3353516/ "TST en NCBI")
- [Forced swim test](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3353513/ "FST en NCBI")
- [Plus maze](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2762911/ "PM en NCBI")

El programa depende de la percepción del usuario y por lo tanto no realiza el análisis de archivos de video de forma autónoma.

Para poder registrar y analizar una prueba, se debe ver al mismo tiempo el experimento o idealmente una grabación de este. No es necesario *pausar* la ejecución del experimento pues el registro de éste se realiza en tiempo real. Para cada tipo de prueba se han determinado *estados* que deberá de indicar el usuario al momento que suceden. El programa identifica y clasifica cada prueba como una de dos tipos.

**Pruebas de dos estados:** Aquí entran las pruebas en las que el animal sujeto de estudio adopta uno de dos estados, un estado de *actividad* o uno de *inactividad*. Las pruebas ideales de esta categoría son *Tail suspension test* y *Forced swim test*.

**Pruebas de tres estados:** Cubre las pruebas en las que el animal opta por tres estados distintos. La prueba ideal de esta categoría es *Plus maze*, en donde se evalúan tres posibles ubicaciones dentro del laberinto.

## Uso del conteo estándar

En la versión actual se pueden realizar dos tipos de conteo de actividad. En el *conteo estándar* el usuario idealmente estará viendo una grabación de la prueba que se realiza. 

Para comenzar a realizar un conteo de este tipo, se deberá ingresar a la opción `1` desde el menú principal, de ahí, el programa requerirá algunos datos para poder realizar un registro apropiado:

- **Fecha de realización del experimento:** Se deberá ingresar la fecha en la que se realizó el experimento, idealmente será a dos dígitos separados por un espacio, comenzando por día seguido del mes y año. Por ejemplo, para registrar un experimento realizado el *14 de marzo del 2017* la entrada ideal será `14 03 17`.
- **Prueba a realizar:** Aquí se deberá especificar el nombre de la prueba que se registrará. Para poder realizar una medición optimizada de una de las tres mencionadas al inicio, se deberá poner un acrónimo del nombre de la prueba en letras mayúsculas. En caso de ingresar una prueba no identificada se realizará por *default* una prueba de dos estados.
    + Para la prueba *Tail Suspension Test* se deberá ingresar `TST`
    + Para la prueba *Forced Swim Test* se deberá ingresar `FST`
    + Para la prueba *Plus Maze* se deberá ingresar `PM`
- **Tiempo de registro:** El tiempo en base al que se realizarán las estadísticas. Se aconseja registrar un poco más del tiempo indicado (*pocos segundos más*) para garantizar que las estadísticas se realicen en base al tiempo indicado. Si se realiza un registro más corto del tiempo especificado las estadísticas se realizarán en base a esa nueva medida. Se deberá especificar las horas, minutos y segundos que idealmente dura la prueba, separados por un espacio.
- **Caracter de fin de registro:** Este caracter será el que habrá que ingresar cuando terminemos de hacer nuestro registro. Al recibir este caracter el programa dejará de grabar los eventos y procederá a realizar las estadísticas.
- **Nombre control del animal:** Este será el nombre de identificación del animal que se esté registrando. Este nombre no deberá tener espacios, de tenerlos el nombre final se recortará al texto antes del primer espacio.
- **Caracteres de espacios:** Para la prueba de *Plus Maze* será necesario indicar los caracteres con los que se señalará que en qué espacio se encuentra el animal, habrá que especificar un caracter distinto para cada espacio. Los espacios que se consideran son *espacios abiertos*, *espacios cerrados* y *espacio central*.

### Realización del registro

Una vez que se ha ingresado la información del experimento, el programa mostrará la pantalla de espera para comenzar a grabar la actividad que el usuario indique. Se mostrará un resumen de la información que ya se ha proporcionado y además se mostrará un código de colores como confirmación a las señales del usuario.

**Pruebas de dos estados:** Una vez que comienza la prueba o la sección desde la que se desea registrar, se deberá presionar cualquier tecla **excepto** la tecla que indica el término del registro (*a menos de que esa sea la intención*). En ese momento el programa dará por hecho que el animal comienza con un estado de actividad y se mostrará el texto de color *verde*. En adelante bastará con presionar cualquier tecla para indicar un cambio en el estado del animal, es decir, cada que el animal pase de estado activo a inactivo o viceversa, se deberá de presionar una tecla cualquiera pero distinta de la tecla de término. Cuando la prueba termine habrá que presionar la tecla de término y así se pasará a las estadísticas.

**Pruebas de tres estados:** Una vez que la prueba comienza se deberá presionar la tecla que corresponde a la ubicación inicial del ratón (*idealmente el espacio central*), y de ahí en adelante se presionará la tecla que indique el espacio en el que el animal ha entrado, ya sea *abierto*, *cerrado* o *central*. Si se presiona una tecla diferente a esas tres y diferente a la tecla de salida, el programa mostrará el texto `Corrección` y lo interpretará como entrada al espacio central. Al terminar el registro se deberá presionar la tecla marcada como de término.

Una vez que hemos terminado de registrar, el programa guardará el registro y las estadísticas generadas por el mismo en el archivo que ha especificado al iniciar el conteo. Adicionalmente se preguntará si se desea realizar otro registro. 

## Uso del conteo por deltas de tiempo

Para esta opción el programa pedirá la información general del experimento a registrar, pero al momento de realizar el conteo se solicitará una entrada escrita que varía según el tipo de prueba:

**Pruebas de dos estados:** Se esperará recibir en milésimas de segundo, el tiempo que transcurre entre cada cambio de estado del animal.
**Pruebas de tres estados:** Se esperará recibir dos parámetros por línea, el primer parámetro indicará la ubicación del animal, donde `0` indica espacio *abierto*, `1` indica espacio central y `2` indica espacio cerrado, como segundo parámetro se esperá el tiempo que el animal duró en el espacio anteriormente dicho expresado en milésimas de segundo.

Para este registro se espera que todas las entradas sean numéricas. Para decir que se ha terminado de ingresar la información se deberá ingresar un `-1`. A continuación el programa realizará la estadística.

Este tipo de registro resulta especialmente útil para volver a realizar la estadística en versiones más recientes del programa. El programa en cada reporte generará un registro como el descrito para la entrada de este conteo.

## Estadísticas realizadas

El programa realiza estadísticas especialmente diseñadas para cada tipo de prueba y con precisión de milésimas de segundo:

### Pruebas de dos estados

Las estadísticas se realizan en todo el intervalo especificado, para los últimos 2/3 del intervalo usado y para los 4/6 intermedios del intervalo usado. Por ejemplo, si se ha realizado un registro de 6 minutos, se realizará la estadística de esos seis minutos de registro, de los últimos cuatro minutos y de los cuatro minutos intermedios de la prueba. La estadística realizada es:

- Tiempo de actividad
- Tiempo de inactividad
- Porcentaje de actividad
- Porcentaje de inactividad
- Tiempo a primera inactividad
- Mayor periodo de actividad
- Mayor periodo de inactividad

### Pruebas de tres estados

- Tiempo en espacios abiertos
- Tiempo en el espacio central
- Tiempo en espacios cerrados
- Porcentaje en espacios abiertos
- Porcentaje en el espacio central
- Porcentaje en espacios cerrados
- Número de entradas a espacios abiertos
- Número de entradas al espacio central
- Número de entradas a espacios cerrados

## Archivos de reporte

Cada reporte que se genera se guarda en una ubicación que sigue la siguiente estructura a partir del lugar de ejecución del programa:

    Registros > [Tipo de prueba] > [Fecha de realización] > 

Y en un archivo que tiene la siguiente estructura en su nombre:

    [Fecha de realización] [Tipo de prueba] [ID del animal].txt

Por ejemplo, la ruta completa de un reporte realizado de una prueba de *TST* el *14 de marzo del 2017* al animal control *C1* será:

    Registros > TST > 14-03-17 > 14-03-17 TST C1.txt

Dentro del archivo se almacena:

- ID del animal
- Prueba realizada
- Fecha del experimento
- Tiempo especificado por el usuario
- Tiempo total registrado
- Tiempo usado de base para las estadísticas
- Estadísticas según el tipo de prueba
- Reporte del registro indicando el estado/posición del animal en el tiempo en que ocurrió
- Reporte completo de deltas de tiempo
- Versión del programa con la que se realizó el reporte

## Desarrollo del programa

Este programa y el concepto fue realizado como una herramienta de apoyo para el [Laboratorio de Neurobiología del estrés](https://www.marcoatzori.org/ "Sitio oficial") de la [Universidad Autónoma de San Luis Potosí](http://www.uaslp.mx/ "Sitio oficial").

> Si te interesa colaborar con esta herramienta sírvete de usar las instancias para reportar [errores o sugerencias](https://github.com/Include-Poetry/LC-Activity-test-counter/issues "Reportar un error o sugerencia") o hacer *fork* y agregar nuevas funcionalidades.

***Más sobre el desarrollador en:*** [Github](https://github.com/Include-Poetry/ "rivel_co").

### Licencia

[GNU General Public License v3.0](https://github.com/Include-Poetry/LC-Activity-test-counter/blob/master/LICENSE "Licencia completa").
# Activity test counter

## Descripción

Este programa es un auxiliar en el análisis y registro de pruebas de conducta. Permite generar estadísticas del experimento con precisión de milésimas de segundo, de forma sencilla y al mismo tiempo en que se observa la prueba o grabación de la misma. Especialmente optimizado para las pruebas:

- [Tail suspension test](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3353516/ "TST en NCBI")
- [Forced swim test](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3353513/ "FST en NCBI")
- [Plus maze](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2762911/ "PM en NCBI")

El programa depende de la percepción del usuario y por lo tanto no realiza el análisis de archivos de video de forma autónoma.

Para poder registrar y analizar una prueba, se debe ver al mismo tiempo el experimento o idealmente una grabación de este. No es necesario *pausar* la ejecución del experimento pues el registro de éste se realiza en tiempo real. Para cada tipo de prueba se han determinado *estados* que deberá de indicar el usuario al momento que suceden. El programa identifica y clasifica cada prueba como una de dos tipos.

**Pruebas de dos estados:** Aquí entran las pruebas en las que el animal sujeto de estudio adopta uno de dos estados, un estado de *actividad* o uno de *inactividad*. Las pruebas ideales de esta categoría son *Tail suspension test* y *Forced swim test*.

**Pruebas de tres estados:** Cubre las pruebas en las que el animal opta por tres estados o posiciones distintas. La prueba ideal de esta categoría es *Plus maze*, en donde se evalúan tres posibles ubicaciones dentro del laberinto.

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

## Uso de las búsquedas

El programa permite realizar dos tipos de búsquedas para pruebas de dos estados, una búsqueda de ***bloque óptimo*** y otra de ***diferencias óptimas***. El objetivo de estas búsquedas es conocer mejor el *comportamiento* de los datos que genera el experimento realizado.

### Búsqueda de bloque óptimo

Esta búsqueda permite encontrar en nuestro registro un segmento de longitud dada en donde se encuentra la mayor parte de la actividad en uno o más registros. Para lograr este análisis es necesario tener un reporte del porcentaje o del tiempo de actividad de un determinado experimento (como los que genera este programa). Cada reporte indica en la primer línea la cantidad de minutos que se registraron, en una cantidad fraccionada de minutos, se *cierra* al número entero siguiente. A continuación se indica en cada línea el porcentaje del tiempo o el tiempo en sí que el animal estuvo en actividad. Un ejemplo es el siguiente

    6      // Se registraron 6 minutos
    35     // 35% de actividad del minuto 0 al 1
    19     // 19% de actividad del minuto 1 al 2
    28     // Del minuto 2 al 3
    27     // Del minuto 3 al 4
    10     // Del minuto 4 al 5
    13     // Del minuto 5 al 6

En caso de registrar por segundos de actividad es el mismo principio.

Si ingresamos el registro anterior a la búsqueda (*sólo los números, claro*) y buscamos el intervalo de **2 minutos** en el que hay más actividad, el programa indicará el espacio temporal del minuto **00:02:00:000 al 00:04:00:000**, abarcando los valores `27` y `28`, si buscamos por el intervalo de 2 minutos en el que hay más inactividad, el programa indicará del minuto 00:04:00:000 al 00:06:00:000, abarcando los valores `10` y `13`. **Es importante considerar que sólo se buscará en minutos contiguos**.

Esta función cobra mayor utilidad cuando realizamos la búsqueda en varios registros distintos entre sí. El programa verá en qué intervalo de longitud dada es en donde se encuentra el mayor porcentaje o tiempo de actividad o inactividad en todos los registros indicados, por lo tanto, la salida dirá el segmento en el que todos los registros en conjunto promedian la mayor cantidad de actividad o inactividad.

Para realizar esta búsqueda, desde el menú principal hay que ingresar a la opción `3`, de ahí a la `1`. A continuación el programa pedirá la cantidad de registros que vamos a evaluar en conjunto, pueden se hasta **100** registros diferentes. Una vez indicada la cantidad de registros, habrá que ingresar el registro temporal por minuto de cada uno. Como ya se mencionaba, se pueden utilizar los porcentajes o los tiempos, pero se deberá ser consistente con todos los registros. Ya que hemos ingresados todos los registros, se preguntará si se quiere optimizar la actividad o la actividad, en caso de escoger actividad, se deberá ingresar `S` o `s`, en caso de escoger inactividad se deberá ingresar `N` o `n`. A continuación se deberá indicar la longitud del bloque que se busca, esto se indica con un número entero que expresa la duración en minutos de dicho bloque. Si se encuentran varios bloques óptimos se mencionarán todos ellos.

### Búsqueda de diferencias óptimas

Esta búsqueda permite encontrar el bloque temporal de longitud dada, en el que existe mayor diferencia en tiempo o porcentaje de actividad entre dos o más registros. El programa solicitará los registros de los que se considerará la actividad y después los registros de los que se considerará la inactividad. Cada registro deberá ser registrado con el formato que se indicó en el apartado anterior sobre el *bloque óptimo*. Si por ejemplo buscamos el segmento temporal de duración de **2 minutos** considerando el siguiente registro como actividad:

    4
    10
    12
    3
    13

Y el siguiente como inactividad:

    4
    2
    10
    34
    12

El programa indicará que el bloque en donde existe una mayor diferencia de actividad es del minuto **00:00:00:000 al 00:02:00:000**. Es importante recordar que en ambos registros indicamos el porcentaje o tiempo de actividad, el programa hará las conversiones necesarias para tomar la inactividad y posteriormente realizar la búsqueda.

Para realizar esta búsqueda desde el menú principal, es necesario ingresar a la opción `3` y a continuación la `2`. De ahí se solicitará la cantidad de registros a tomar como activos y la cantidad a tomar como inactivos. Estos valores no necesariamente tienen que ser iguales, pues ambos son normalizados antes de realizar la búsqueda. Después de ingresar todos los registros, habrá que indicar la duración en minutos del bloque que estamos buscando. Si se encuentran varios bloques óptimos se mostrarán todos ellos.

## Estadísticas realizadas

El programa realiza estadísticas especialmente diseñadas para cada tipo de prueba y con precisión de milésimas de segundo:

### Pruebas de dos estados

Las estadísticas se realizan en todo el intervalo especificado. La estadística realizada es:

- Tiempo de actividad
- Tiempo de inactividad
- Porcentaje de actividad
- Porcentaje de inactividad
- Tiempo a primera inactividad
- Mayor periodo de actividad
- Mayor periodo de inactividad
- Promedio de fase de actividad
- Promedio de fase de inactividad
- Cantidad de episodios de actividad
- Cantidad de episodios de inactividad
- Porcentaje de actividad por cada minuto
- Tiempo de actividad por cada minuto

### Pruebas de tres estados

- Tiempo en espacios abiertos
- Tiempo en el espacio central
- Tiempo en espacios cerrados
- Porcentaje de tiempo en espacios abiertos
- Porcentaje de tiempo en el espacio central
- Porcentaje de tiempo en espacios cerrados
- Número de entradas a espacios abiertos
- Número de entradas al espacio central
- Número de entradas a espacios cerrados
- Porcentaje de entradas a espacios abiertos
- Porcentaje de entradas al espacio central
- Porcentaje de entradas a espacios cerrados

### Formato de las estadísticas

Cada una de las estadísticas mencionadas se guardan con dos formatos en el mismo archivo, una versión *para humanos* y otra versión *para computadoras*.

#### Versión para humanos

Esta versión de la estadística tiene como objetivo ser leída fácilmente por el usuario, incluye el texto que indica el nombre de cada parámetro medido y un formato adecuado para las medidas temporales. En el caso de un registro de dos estados se generá una salida como la siguiente:

    - Datos para humanos
    Tiempo de actividad:             00:02:47:687
    Tiempo de inactividad:           00:03:12:313
    Porcentaje de actividad:         46.5797 %
    Porcentaje de inactividad:       53.4203 %
    Tiempo a primera inactividad:    00:00:03:316
    Mayor periodo de actividad:      00:00:14:289
    Mayor periodo de inactividad:    00:00:37:522
    Promedio de fase de actividad:   00:00:03:422
    Promedio de fase de inactividad: 00:00:04:006
    Episodios de actividad:          49
    Episodios de inactividad:        48

#### Versión para computadoras

Aquí los datos se *imprimen* omitiendo el nombre del parámetro medido y los tiempos son indicados en segundos. Es importante considerar que en este formato se guardan los mismos datos que en el *formato para humanos*, pero el formato facilita el *copiar y pegar* la información y ser reutilizada en hojas de cálculo, por ejemplo. La misma información anteriormente mencionada se guardaría como sigue:

    + Datos para computadoras (en segundos):
    167.687
    192.313
    46.5797
    53.4203
    3.316
    14.289
    37.522
    3.422
    4.006
    49
    48

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
- Estadísticas según el tipo de prueba en ambos formatos
- Reporte del registro indicando el estado/posición del animal en el tiempo en que ocurrió
- Reporte completo de deltas de tiempo
- Versión del programa con la que se realizó el reporte

## Desarrollo del programa

Este programa y el concepto fue realizado como una herramienta de apoyo para el [Laboratorio de Neurobiología del estrés](https://www.marcoatzori.org/ "Sitio oficial") de la [Universidad Autónoma de San Luis Potosí](http://www.uaslp.mx/ "Sitio oficial").

> Si te interesa colaborar con esta herramienta sírvete de usar las instancias para reportar [errores o sugerencias](https://github.com/Include-Poetry/LC-Activity-test-counter/issues "Reportar un error o sugerencia") o hacer *fork* y agregar nuevas funcionalidades.

***Más sobre el desarrollador en:*** [Github](https://github.com/Include-Poetry/ "rivel_co").

### Licencia

[GNU General Public License v3.0](https://github.com/Include-Poetry/LC-Activity-test-counter/blob/master/LICENSE "Licencia completa").
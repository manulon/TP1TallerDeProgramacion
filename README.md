# TP1-CipherHill
# Alumno: Manuel Longo Elia
# Padrón: 102425

En este trabajo se implementa un programa que actúa por un lado como cliente y por el otro como servidor. El rol del cliente es el de leer un archivo y enviar sus lineas al servidor. El servidor recibe los mensajes y los encripta mediante la encriptacion de cipher hill, para luego enviarlo nuevamente al cliente ya encriptado.

El siguiente informe detalla información relevante del proceso de desarrollo del programa: su esqueleto, diagrama de clases y problemas que surgieron al realizarlo.

# DISEÑO

Antes de implementar la solución, se empezó por diseñarla, planteando las diferentes estructuras del programa y cómo iban a relacionarse entre sí. 

El diseño se pensó usando como base la programación orientada a objetos.

Se plantearon los siguientes:

- PLAINTEXT: (o ciphertext) un TDA que representa al elemento que sera encriptado por el encriptador y servira para definir el mensaje final que sera enviado al cliente. Posee dos atributos *line* representa a la cadena de caracteres a encriptar y *line_length* que representa el largo de dicha cadena.

- SOCKET: un TDA socket con los métodos necesarios para poder efectuar la comunicación entre cliente y servidor: abrir el socket, esperar a una conexión, aceptarla, enviar y recibir mensajes a través del mismo, y finalmente cerrar el socket correctamente.


- CIPHER HILL ENCRYPTOR: este TDA seria el corazon de este programa, es el encargado de realizar y delegar todos los pasos de la encriptacion. Posee los atributos *password* que hace referencia a la contraseña leida, *message_to_encrypt* que es el mensaje que ira pasando por todos los pasos de encriptacion, tambien esta *message_to_encrypt_length* que como todos los TDA representa el largo de dicho mensaje. Y finalmente *final_plaintext* que sera el plaintext resultante de toda la encriptacion.

- MATRIX: un TDA que representa a la matriz que se utilizara para hacer el paso final de la encriptacion, fue creada para delegar el producto matricial y posee 3 atributos, su dimension, el largo inicial de la contraseña y la matriz en si.

- PASSWORD: un TDA que representa a la key que se ingresa cuando se crea al servidor,.

- CLIENTE: TDA que contiene los atributos necesarios para entablecer una conexion con el servidor y leer un archivo. Tambien dos atributos que hacen referencia al mensaje que este quiere enviar al servidor, como *message* y *message_lenght*.

- SERVIDOR: TDA que use a los mencionados anteriormente para cumplir su función: abrir un socket, esperar a recibir un mensaje, encriptarlo y enviarlo nuevamente al cliente.

- FILE READER: para delegar responsabilidad, se pensó este TDA con la función de leer un archivo y enviar las lineas al cliente. Va a ser usado por el cliente cuando corresponda. *VER APARTADO IMPLEMENTACIONES PARA REENTREGA*


# IMPLEMENTACIÓN

Para la implementacion se busco siempre cumplir con el paradigma de programacion orientada a objetos, algo que es un poco dificil en c ya que estos no tienen objetos en si. En todo momento se intento no romper con el encapsulamiento y delegar comportamientos. Asimismo tambien cumplir con los principios SOLID.

# IMPLEMENTACIONES PARA REENTREGA

En este apartado voy a mostrar un agregado que me gustaria agregarle al programa para que quede un poco mas orientado a objetos posible. En la clase *file_reader* mas precisamente en el metodo *file_reader_iterator* este metodo viola los principios de programacion orientada a objetos ya que la clase no esta teniendo una unica responsabilidad. El file reader solamente debe encargarse de leer el archivo y enviar las lineas que lee al cliente, en cambio en la implementacion presentada es el file reader quien lee y envia al servidor los mensajes, lo cual esta mal.
Lo ideal seria que haya un metodo llamado *file_reader_get_chunk* que lo que haga es obtener un *chunk* del archivo y que este sea enviado al cliente para que lo procese como mensaje y lo envie al servidor. Esta implementacion para esta entrega no pudo ser implementada ya que hubo un problema que surgio en la etapa de elaboracion del programa que explicare en el apartado siguiente.

# Problemas

Como se puede ver, mi codigo no pasa las ultimas dos pruebas del sercom *msg_long* y *msgnl*. La segunda prueba tiene como archivo de entrada un "\n" solamente y como resultado deberia mostrase lo mismo en el stdout. Pero con la implementacion que arme yo esto pasaba a veces solamente, cuando probaba en mi entorno local, a veces la prueba corria perfectametne y otras se quedaba colgada en el medio entre la respuesta del servidor y la recepcion final del cliente. Estuve dos dias intentando ver por que pasaba eso pero no logre conseguirlo. Mi sospecha es que debe haber algun buffer overflow en algun lado o debo tener mal implemetado los receive y send. Pero no llegue a encontrar esos errores.
Para la prueba de *msg_long* tuve una situacion similar. Muchas veces en mi entorno me ha pasado que la primer linea se imprime perfectamente y luego se cuelga, o las primeras dos bien y luego nada. O hasta tambien la primer linea impresa con la mitad de caracteres bien y la otra mitad mal de manera aleatoria. Esta situacion fue la que mas indicios me dio de un buffer overflow, que como repito, no pude encontrarlo. Uno de los posibles detonantes de el error tambien puede ser que esta prueba tiene lineas en su input que solamente son un "\n" que vendria a ser la prueba *msgnl*, al tenerla integrada y yo tener mal esa prueba tambien eso no ayuda al funcionamiento correcto del programa. 

# Diagrama de clases representativo de la solución final:

imagen...

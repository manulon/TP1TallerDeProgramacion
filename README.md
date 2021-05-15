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

- SOCKET: un TDA socket con los métodos necesarios para poder efectuar la comunicación entre cliente y servidor: abrir el socket, esperar a una conexión, aceptarla y finalmente cerrar el socket correctamente.

- CIPHER HILL ENCRYPTOR: este TDA seria el corazon de este programa, es el encargado de realizar y delegar todos los pasos de la encriptacion. Posee los atributos *password* que hace referencia a la contraseña leida, *message_to_encrypt* que es el mensaje que ira pasando por todos los pasos de encriptacion, tambien esta *message_to_encrypt_length* que como todos los TDA representa el largo de dicho mensaje. Y finalmente *final_plaintext* que sera el plaintext resultante de toda la encriptacion.

- MATRIX: un TDA que representa a la matriz que se utilizara para hacer el paso final de la encriptacion, fue creada para delegar el producto matricial y posee 3 atributos, su dimension, el largo inicial de la contraseña y la matriz en si.

- PASSWORD: un TDA que representa a la key que se ingresa cuando se crea al servidor.

- CLIENTE: TDA que contiene los atributos necesarios para entablecer una comunicacion con el servidor, obtener el mensaje a enviar de un archivo y decodificar el mensaje recibido.

- SERVIDOR: TDA que contiene los atributos necsarios para entablecer una comunicacion con el cliente.

- FILE READER: para delegar responsabilidad, se pensó este TDA con la función de leer un archivo y setear las lineas como mensaje al cliente que lo ha invocado.

- CLIENT PROTOCOL: TDA que se asegura de respetar el protocolo de envio y recepcion de mensajes por parte del cliente.

- SERVER PROTOCOL: TDA que se asegura de respetar el protocolo de envio y recepcion de mensajes por parte del servidor. 

- COMMUNICATION PROTOCOL: TDA creado para realizar el envio de mensajes para cliente y servidor.

# IMPLEMENTACIÓN

Para la implementacion se busco siempre cumplir con el paradigma de programacion orientada a objetos, algo que es un poco dificil en c ya que estos no tienen objetos en si. En todo momento se intento no romper con el encapsulamiento y delegar comportamientos. Asimismo tambien cumplir con los principios SOLID.

# CAMBIOS REENTREGA

- Se ha corregido el cierre de flujos estandar en `client.c.`
- Se ha corregido el shadowing a la funcion `file_reader_read_chunk` y se ha cambiado la implementacion de esta para que sea mas facil para el autor.
- Se ha corregido la mezcla de niveles de abstraccion en `file_reader_read_chunk` y `server_cipher_hill_encryptor`
- Se ha corregido el `socket_init` para que el file descriptor se obtenga dentro de esta funcion y asi respetar el encapsulamiento
- Se han corregido pequeñas partes logicas de `plaintext_fill_with_zero()` que no permitian el funcionamiento correcto del programa. Asimismo con partes de la funcion `_send_message`.
- Se han agregado variables intermedias en `matrix_product` para aportarle legibilidad al codigo.
- Se han implementado los TDA `client_protocol`, `server_protocol` y `common_protocol` que aseguran el cumplimiento correcto del protocolo propuesto por la catedra para el envio de los mensajes.

# Problemas

Para esta entrega no se han reportado problemas al realizar el trabajo.

# Diagrama de clases representativo de la solución final:

Este diagrama representa la relacion entre las clases. ![DiagramaDeClases](https://user-images.githubusercontent.com/45469722/118380149-0b1c2000-b5b6-11eb-9dd1-e9924644a289.png)


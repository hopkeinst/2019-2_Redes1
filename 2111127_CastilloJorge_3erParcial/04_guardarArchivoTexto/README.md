# 04 - Guardar un archivo de texto

Consiste en pasar un archivo de texto desde un cliente a un servidor. El cliente carga el archivo y este se almacena en el servidor. Los archivos que son guardados en el servidor se les antepone la cadena 's_'.
En esta carpeta, se pueden observar estos archivos.

__¿COMO COMPILAR?__
Para utilizar este par de programas primero debe compilarlos
utilizando el comando

`make all`

Este programa busca las instrucciones del archivo Makefile
y las ejecuta para generar los binarios, es decir, 
va a crear dos programas ejecutables: client y server

__¿COMO EJECUTAR?__
Abra un terminal y ejecute

`./server`

Abra otro terminal y ejecute

`./cliente localhost nombreDelArchivoTexto`

Puede ejecutar el servidor en un computador y el cliente
en otro computador. Para ello debe modificar el comando
del cliente como:

`./client IP_DEL_SERVIDOR nombreDelArchivoTexto`

Donde _IP_DEL_SERVIDOR_ es la dirección IP del computador
donde ejecutó el comando del servidor: "server" 


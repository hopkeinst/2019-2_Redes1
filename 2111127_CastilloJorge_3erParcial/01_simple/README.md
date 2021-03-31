# 01 - Conexión Simple

Permite conectar el cliente y el servidor a través de un socket de red y cuando lo hace muestra un mensaje.

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

`./cliente localhost`

Puede ejecutar el servidor en un computador y el cliente
en otro computador. Para ello debe modificar el comando
del cliente como siguie:

`./client IP_DEL_SERVIDOR`

Donde _IP_DEL_SERVIDOR_ es la dirección IP del computador
donde ejecutó el comando del servidor: "server" 

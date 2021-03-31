/**
* Programa que recibe a través de un socket de Flujos de datos un mensaje de un cliente.
* Redes de Computadoras I
* Universidad Industrial de Santander
* ENTRADA: NA
* SALIDA: el mensaje que viene del cliente
* PROCESO: Este programa se queda esperando (Listen) por alguna conexión por parte de
* un cliente. Cuando recibe una solicitud, la acepta, recibe el mensaje y la muestra
* por pantalla
**/


#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

// PUERTO UTILIZADO PARA LA TRANSMISIÓN 
#define PORT 2048

// EL NÚMERO DE CONEXIONES PERMITIDAS 
#define BACKLOG 10 


// PROGRAMA PRINCIPAL
int main() {
	int numbytes, MaxData=1024;
	char buf[MaxData];
	char *clientIP;

	// DESCRIPTORES PARA LA GESTIÓN DEL SOCKET
	int fd, fd2; 

	// DECLARACIÓN DEL SOCKET DEL SERVIDOR
	struct sockaddr_in server; 

	// DECLARACIÓN DEL SOCKET DEL CLIENTE
	struct sockaddr_in client; 

	int sin_size;

	// CREACIÓN DE UN EXTREMO DE LA COMUNICACIÓN
	if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {  
		// SI NO SE PUEDE CREAR SE MUESTRA UN ERROR 
		// Y EL PROGRAMA TERMINA
		printf("error en socket()\n");
		exit(-1);
	}

// ESPECIFICACIÓN DE VALORES AL SOCKET DEL SERVIDOR
//
	// SE INDICA QUE SE UTILIZARÁ IPv4
	server.sin_family = AF_INET;         

	// SE INDICA EL PUERTO DEL SOCKET
	server.sin_port = htons(PORT);
 
	// INADDR_ANY INDICA QUE SE UTILIZARÁ LA IP ASIGNADA ACTUALMENTE
	server.sin_addr.s_addr = INADDR_ANY; 

	// SE LLENA CON CEROS EL RESTO DE LOS CAMPOS DEL SOCKET
	bzero(&(server.sin_zero),8); 


	// CONEXIÓN DEL SOCKET CON LA INTERFAZ DE RED QUE TIENE LA IP
	// ESPECIFICADA. COMO SE ESPECIFICÓ CUALQUIERA, ENTOCES SE
	// CONECTA CON TODAS LAS INTERFACES
	if(bind(fd,(struct sockaddr*)&server, sizeof( server))==-1) {
		printf("error en bind() \n");
		exit(-1);
	}     

	// SE PONE A ESCUCHAR AL SOCKET
	if(listen(fd,BACKLOG) == -1) {  
		printf("error en listen()\n");
		exit(-1);
	}

	// EL SERVIDOR SE QUEDA EN UN LAZO INFINITO ATENDIENDO SOLICITUDES
	while(1){
		sin_size=sizeof(struct sockaddr_in);

		// SI LLEGA UNA SOLICITUD SE ACEPTA
		if ((fd2 = accept(fd,(struct sockaddr *)&client, (socklen_t *) &sin_size))==-1) {
			printf("error en accept()\n");
			exit(-1);
		}
		//SE OBTIENE LA IP DEL CLIENTE
		clientIP=inet_ntoa(client.sin_addr);

		// SE MUESTRA POR PANTALLA LA IP DEL CLIENTE
		printf("Se obtuvo una conexion desde %s\n", clientIP ); 

		// SE ENVÍA UN MENSAJE DE BIENVENIDA AL CLIENTE
		send(fd2,"Bienvenido a mi servidor.\n",24,0); 
      	
		// SE RECIBE UN MENSAJE DESDE EL CLIENTE
		// ESTE SE ALMACENA EN UN BUFFER (buf)
		if(numbytes=recv(fd2,buf,1024,0)==-1){
			printf("Error en recv()\n");
			exit(-1);
		}

		// SE AGREGA UN FIN DE CADENA AL BUFFER
		buf[strlen(buf)+1]='\0';
		// SE MUESTRA LA CANTIDAD DE BYTES DEL MENSAJE
		printf("%d \n", numbytes);
		// SE MUESTRA LA LONGITUD DEL BUFFER
		printf("%ld \n", strlen(buf));
		// SE MUESTRA EL MENSAJE
		printf("Mensaje Recibido: %s \n", buf);

		// SE ENVIA UN MENSAJE AL CLIENTE INDICANDO QUE SE RECIBIÓ
		// EL MENSAJE 
		// send(fd2,"Recibido************\n",1024,0); 
	  
		// SE CIERRA LA CONEXIÓN CON EL CLIENTE
		close(fd2); 
	}
	return(0);
}


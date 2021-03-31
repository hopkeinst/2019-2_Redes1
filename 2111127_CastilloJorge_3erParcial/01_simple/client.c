/**
* Programa que envía a través de un socket de Flujos de datos un mensaje a un servidor.
* Redes de Computadoras I
* Universidad Industrial de Santander
* ENTRADA: IP o nombre del servidor
* SALIDA: NA
* PROCESO: Este programa crea un socket y recibe un mensaje de bienvenida del servidor,
* envía un mensaje de texto a un servidor y finalmente recibe un mensaje de recibido
**/


#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>        
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// PUERTO DEL SERVIDOR
#define PORT 2048         

// EL TAMAÑO MÁXIMO DE DATOS
#define MAXDATASIZE 100   


int main(int argc, char *argv[]){

	// DESCRIPTOR PARA LA GESTIÓN DEL SOCKET
	int fd;
	int numbytes;       

	// BUFFER PARA ALMACENAR LOS DATOS
	char buf[MAXDATASIZE];  

	// ESTRUCTURA PARA ALMACENAR LA INFORMACIÓN
	// DEL SERVIDOR
	struct hostent *he;         

	// DECLARACIÓN DEL SOCKET DEL SERVIDOR
	struct sockaddr_in server;
  
	char band;

	// EL MENSAJE QUE SE ENVIARÁ AL SERVIDOR
	char message[1024]="Este es el mensaje enviado";

	// VALIDACIÓN DE LOS PARÁMETROS DE ENTRADA
	if (argc !=2) { 
		printf("Uso: %s <Dirección IP o Nombre>\n",argv[0]);
		exit(-1);
	}


	// OBTENER EL NOMBRE DEL SERVIDOR O LA IP
	if ((he=gethostbyname(argv[1]))==NULL){       
		printf("gethostbyname() error\n");
		exit(-1);
	}

	// CREACIÓN DE UN EXTREMO DE LA COMUNICACIÓN
	if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
		printf("socket() error\n");
		exit(-1);
	}

// ESPECIFICACIÓN DE VALORES AL SOCKET DEL SERVIDOR
//
	// SE ESPECIFICA QUE SE UTILIZARÁ IPv4
	server.sin_family = AF_INET;

	// SE ESPECIFICA EL PUERTO DEL SOCKET
	server.sin_port = htons(PORT); 

	// SE ESPECIFICA LA IP O NOMBRE DEL SERVIDOR QUE VIENE
	// DE LA FUNCIÓN gethostbyname
	server.sin_addr = *((struct in_addr *)he->h_addr);  

	// SE LLENA CON CEROS EL RESTO DE LOS CAMPOS DEL SOCKET
	bzero(&(server.sin_zero),8);

	// SE REALIZA LA CONEXIÓN AL SERVIDOR
	if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1){ 
		printf("connect() error\n");
		exit(-1);
	}

	// SE HACE LA RECEPCIÓN DEL MENSAJE DE BIENVENIDA DEL SERVIDOR
	if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  
		printf("Error en recv() \n");
		exit(-1);
	}

	// SE AGREGA UN FIN DE CADENA AL BUFFER DE RECEPCIÓN
	buf[numbytes]='\0';

	// SE MUESTRA EL MENSAJE DE BIENVENIDA
	printf("Mensaje del Servidor: %s\n",buf); 

	// SE ENVÍA EL MENSAJE
	send(fd,message,strlen(message)+1,0);

	// SE CIERRA LA CONEXIÓN CON EL SERVIDOR
	close(fd);   
  
}

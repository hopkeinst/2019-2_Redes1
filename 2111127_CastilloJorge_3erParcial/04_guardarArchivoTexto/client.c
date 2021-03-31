/**
* Programa que envia a traves de un socket de Flujos de datos un mensaje a un servidor.
* Redes de Computadoras I
* Universidad Industrial de Santander
* ENTRADA: IP o nombre del servidor
* SALIDA: NA
* PROCESO: Este programa crea un socket y recibe un mensaje de bienvenida del servidor,
* envia un mensaje de texto a un servidor y finalmente recibe un mensaje de recibido
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

// EL TAMANO MAXIMO DE DATOS
#define MAXDATASIZE 100   


int main(int argc, char *argv[]){

	// DESCRIPTOR PARA LA GESTION DEL SOCKET
	int fd;
	int numbytes;
	char *d, linea[1024];

	// DESCRIPTOR PARA LA GESTION DEL ARCHIVO TEXTO
	FILE *ar;

	// BUFFER PARA ALMACENAR LOS DATOS
	char buf[MAXDATASIZE];  

	// ESTRUCTURA PARA ALMACENAR LA INFORMACION
	// DEL SERVIDOR
	struct hostent *he;         

	// DECLARACION DEL SOCKET DEL SERVIDOR
	struct sockaddr_in server;
  
	char band;

	// EL MENSAJE QUE SE ENVIARA AL SERVIDOR
	char message[1024]="Este es el mensaje enviado";

	// VALIDACION DE LOS PARAMETROS DE ENTRADA
	if (argc !=3) { 
		printf("Uso: %s <Direccion IP o Nombre de Host>  <nombreDelArchivo> \n",argv[0]);
		exit(-1);
	}

	//ABRIR EL ARCHIVO TEXTO
	if( (ar = fopen(argv[2], "r")) == NULL ){
		fprintf(stderr, "Falla al abrir el archivo %s \n", argv[2]);
		exit(1);
	}


	// OBTENER EL NOMBRE DEL SERVIDOR O LA IP
	if ((he=gethostbyname(argv[1]))==NULL){       
		printf("gethostbyname() error\n");
		exit(-1);
	}

	// CREACION DE UN EXTREMO DE LA COMUNICACION
	if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
		printf("socket() error\n");
		exit(-1);
	}

// ESPECIFICACION DE VALORES AL SOCKET DEL SERVIDOR
//
	// SE ESPECIFICA QUE SE UTILIZARA IPv4
	server.sin_family = AF_INET;

	// SE ESPECIFICA EL PUERTO DEL SOCKET
	server.sin_port = htons(PORT); 

	// SE ESPECIFICA LA IP O NOMBRE DEL SERVIDOR QUE VIENE
	// DE LA FUNCION gethostbyname
	server.sin_addr = *((struct in_addr *)he->h_addr);  

	// SE LLENA CON CEROS EL RESTO DE LOS CAMPOS DEL SOCKET
	bzero(&(server.sin_zero),8);

	// SE REALIZA LA CONEXION AL SERVIDOR
	if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1){ 
		printf("connect() error\n");
		exit(-1);
	}

	// SE INICIALIZA EL BUFFER
	//strcpy(buf, "");

	// Envio nombre del archivo
	write(fd, argv[2], 100);

	// SE ENVIA EL ARCHIVO TEXTO LINEA POR LINEA
	while( (d = fgets(buf,256,ar)) != NULL ){
		write(fd,buf,strlen(buf));
	}

	// SE CIERRA LA CONEXION CON EL SERVIDOR
	close(fd);   
  
	return 0;
}


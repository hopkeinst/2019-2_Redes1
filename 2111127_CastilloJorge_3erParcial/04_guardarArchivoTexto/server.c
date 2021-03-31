/**
* Programa que recibe a traves de un socket de Flujos de datos un mensaje de un cliente.
* Redes de Computadoras I
* Universidad Industrial de Santander
* ENTRADA: NA
* SALIDA: el mensaje que viene del cliente
* PROCESO: Este programa se queda esperando (Listen) por alguna conexion por parte de
* un cliente. Cuando recibe una solicitud, la acepta, recibe el mensaje y la muestra
* por pantalla
**/


#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

// PUERTO UTILIZADO PARA LA TRANSMISION 
#define PORT 2048

// EL NUMERO DE CONEXIONES PERMITIDAS 
#define BACKLOG 10 


// PROGRAMA PRINCIPAL
int main() {
	int numbytes, MaxData=1024;
	char buf[MaxData];
	memset(buf, 0, MaxData);
	char *clientIP;

	// DESCRIPTORES PARA LA GESTION DEL SOCKET
	int fd, fd2; 

	// DECLARACION DEL SOCKET DEL SERVIDOR
	struct sockaddr_in server; 

	// DECLARACION DEL SOCKET DEL CLIENTE
	struct sockaddr_in client; 

	int sin_size;

	// Para manejar el archivo recibido
	FILE* archivo;

	// Para el nombre del archivo
	char nArchivo[100];
	memset(nArchivo, 0, 100);
	nArchivo[0] = 's';
	nArchivo[1] = '_';

	// CREACION DE UN EXTREMO DE LA COMUNICACION
	if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {  
		// SI NO SE PUEDE CREAR SE MUESTRA UN ERROR 
		// Y EL PROGRAMA TERMINA
		printf("error en socket()\n");
		exit(-1);
	}

// ESPECIFICACION DE VALORES AL SOCKET DEL SERVIDOR
//
	// SE INDICA QUE SE UTILIZARA IPv4
	server.sin_family = AF_INET;         

	// SE INDICA EL PUERTO DEL SOCKET
	server.sin_port = htons(PORT);
 
	// INADDR_ANY INDICA QUE SE UTILIZARA LA IP ASIGNADA ACTUALMENTE
	server.sin_addr.s_addr = INADDR_ANY; 

	// SE LLENA CON CEROS EL RESTO DE LOS CAMPOS DEL SOCKET
	bzero(&(server.sin_zero),8); 


	// CONEXION DEL SOCKET CON LA INTERFAZ DE RED QUE TIENE LA IP
	// ESPECIFICADA. COMO SE ESPECIFICO CUALQUIERA, ENTOCES SE
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

	printf(" => Escuchando el servidor\n");

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

		read(fd2, buf, 100);
		printf("Nombre del archivo original transmitido: %s\n", buf);
		strcat(nArchivo, buf); // Nombre del archivo donde se almacenara lo recibido
		printf("Nombre del archivo en el servidor: %s\n", nArchivo);
		/*
		printf("#############################################################\n");
		printf(" Contenido del archivo recibido y transmitido por el cliente\n");
		printf("#############################################################\n");
		*/

		archivo = fopen(nArchivo, "w+"); // Crea el archivo donde se almacenara lo recibido

		// SE HACE UN LAZO PARA RECIBIR LINEA POR LINEA
		// EL ARCHIVO
		while(read(fd2,buf,1024) > 0){
			// SE MUESTRA EL CONTENIDO DEL BUFFER
			// ES DECIR, UNA LINEA DEL ARCHIVO TEXTO
			//printf("%s ", buf);
			fputs(buf, archivo); // Escribe en el archivo
		}

		// Para 
		printf("#############################################################\n");
		printf(" Contenido del archivo recibido y transmitido por el cliente\n");
		printf(" guardado en el archivo %s\n", nArchivo);
		printf("#############################################################\n");

		// SE CIERRA LA CONEXION CON EL CLIENTE
		close(fd2);
		// Cierra el archivo 
		fclose(archivo);
		
		memset(buf, 0, MaxData);
		memset(nArchivo, 0, 100);
		nArchivo[0] = 's';
		nArchivo[1] = '_';

	}
	return(0);
}


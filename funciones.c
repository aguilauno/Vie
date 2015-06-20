/* 
 * Archivo: funciones.c
 * Este archivo contiene las funciones necesarias para la implementación del
 * problema planteado en el proyecto.
 *
 * Autores: Carlos Plantijn # Carnet 10-10572
 *  		Meggie Sanchez  # Carnet 11-10939
 */

#include "funciones.h"

/* cmpfunc
* Comparador de enteros.
* a: apuntador de un número entero
* b: apuntador de un número entero
* retorna la resta de ambos números
*/ 
int cmpfunc(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

/* secuenciaRandom
* Crea un arreglo con numeros aleatorios que están ordenados.
* tamSecuencia: tamaño del arreglo
* randMax: número máximo posible que se puede obtener del random
* pidHijo: número pid del hijo
* retorna el arreglo ordenado de menor a mayor
*/ 
int *secuenciaRandom(int tamSecuencia, int randMax, int pidHijo) {
	/* Utilizando el algoritmo Floyd para evitar números repetidos */
	unsigned char utilizado[randMax];
	memset(utilizado, 0, randMax * sizeof(unsigned char)); /* flags */ 

	int in, im;
	int randi;
	int *arreglo = malloc(sizeof(int) * tamSecuencia); 
	im = 0;

	/* Se inicializa la semilla del random con time() y pidHijo */
	srand(time(NULL) + pidHijo);

	for (in = randMax - tamSecuencia; in < randMax && im < tamSecuencia; ++in) {

		int r = rand() % (in + 1); /* Se genera un número aleatorio 'r' */

		if (utilizado[r]) {
			/* Si ya existe 'r' */
			r = in; /* Se utliza 'in' en lugar de 'r' */
		}

		assert(!utilizado[r]);
		arreglo[im++] = r + 1; /* Para que el rango empiece en 1 */
		utilizado[r] = 1;
	}

	assert(im == tamSecuencia);

	/* Ordenamos el arreglo */
    qsort(arreglo, tamSecuencia, sizeof(int), cmpfunc);
    
    return arreglo;
}

/* AccesoCarpetas
* Accede a las carpetas correspondientes para hacer la verificación de si son 
* directorios o no.
* dir: directorio en el que se hará acceso para lectura de carpetas y archivos
* n: cantidad de elementos a recorrer en el arregloDirectorios
* m: cantidad de elementos a recorrer en el arregloTextos
* j: iteracion en la que se encuentra el proceso hijo
* arregloDirectorios: arreglo que contiene cada uno de los números que 
* representan las carpetas a los que accesará cada uno de los procesos hijos
* arregloTextos: arreglo que contiene cada uno de los números que representan
* los archivos a los que accesará cada uno de los procesos hijos
* argc: cantidad de argumentos de la ejecución principal
* cadena: string donde se encuentra el directorio principal
* fd: pipe para procesos
* superbuffer: buffer grande que guardará todos los archivos correspondientes 
* a un hijo
* retorna el contador de archivos que procesó
*/ 
int AccesoCarpetas(DIR *dir, int n, int m, int j, int *arregloDirectorios, int *arregloTextos, int argc, char *cadena, int fd[], char *superbuffer) {

	struct stat bstat; 		
	struct dirent *direntd;
	struct dirent *direntd2;
	direntd = readdir(dir);

	int tam, rpta, contArchivosProc;
	tam = (unsigned) strlen(dir);

	rpta = *(arregloDirectorios + j);

	char *texto, *nombre, *directorioPrin;	
	DIR *dir2;

/*	while ( (direntd = readdir(dir) ) != NULL) {
 	  	printf("%d\t%d\t%d\t%s\n", direntd->d_ino, direntd->d_off, direntd->d_reclen, direntd->d_name);
 	}*/
/*
	if (strcmp(direntd->d_name, texto) == 0)
		printf("HOLAAAAAAAAAAAAAA%s\n", direntd->d_name);*/

	texto = (char *)malloc(sizeof(char)*TAM);
	nombre = (char *)malloc(sizeof(char)*TAM);
	directorioPrin = (char *)malloc(sizeof(char)*tam);

	sprintf(texto, "%d", rpta);

	if (argc == 6) {
		strcpy(directorioPrin, cadena);
		strcpy(nombre, directorioPrin);
		strcat(nombre, "/");
		strcat(nombre, texto);
		strcat(nombre,"\0");
		//printf("%s\n", nombre);	
	}
	else if (argc == 4) {
		getcwd(directorioPrin, TAM);
		strcpy(nombre, directorioPrin);
		strcat(nombre, "/");
		strcat(nombre, texto);
		strcat(nombre,"\0");
		//printf("%s\n", nombre);
	}

	if (stat(nombre, &bstat) != 0) {
		perror(" No se pudo obtener la informacion de la carpeta ");
    	exit(-1);	
	}
	else if (S_ISDIR(bstat.st_mode)) {
		printf(" Es un directorio\n\n");
	}

	else {
		printf(" No es un directorio \n");
		exit(-1);
	}

	if ( (dir2 = opendir(texto)) == NULL) {

		perror(" No se puede abrir el directorio ya que no existe ");
		exit(1);
	}
	else {
		//printf(" El directorio actual es %s\n", texto);
	}

	direntd2 = readdir(dir2);

	contArchivosProc = AccesoArchivos(dir2, m, arregloTextos, nombre, fd, superbuffer);

	free(directorioPrin);
	free(texto);
	free(nombre);
	closedir(dir2);

	return(contArchivosProc);
}

/* AccesoArchivos
 * Accede a los archivos correspondientes para la verificación de si son 
 * archivos regulares o no
 * dir2: directorio donde ya se accede a las carpetas existentes del 1 al 10
 * m: cantidad de elementos a recorrer en el arregloTextos
 * arregloTextos: arreglo que contiene cada uno de los números que representan
 * los archivos a los que accesará cada uno de los procesos hijos
 * nombre: string que guarda la ruta donde estan las carpetas desde el 
 * directorio principal
 * fd: pipe para comunicacion de procesos
 * superbuffer: buffer para guardar los archivos de un hijo
 * retorna contador de archivos que procesó
 */
int AccesoArchivos(DIR *dir2, int m, int *arregloTextos, char *nombre, int fd[], char *superbuffer) {
	
	int i,rpta,tam2, contArchivosProc;
	struct stat bstat2; 		
	char *texto, *directorioActual;
	tam2 = (unsigned) strlen(dir2);

	contArchivosProc = 0;

	for (i = 0; i < m; i++) {

		texto = (char *)malloc(sizeof(char)*TAM);
		directorioActual = (char *)malloc(sizeof(nombre)+64);

		rpta = *(arregloTextos + i);
		sprintf(texto, "%d", rpta);
		
		strcpy(directorioActual, nombre);
		strcat(directorioActual, "/");
		strcat(directorioActual, texto);
		strcat(directorioActual,"\0");
		printf("\n%s\n", directorioActual);

		if (stat(directorioActual, &bstat2) != 0) {
			perror(" No se pudo obtener la informacion del archivo ");
		}

		else if (S_ISREG(bstat2.st_mode)) {

			printf(" Es un archivo regular\n");
			contArchivosProc++;

			char *buffer;
			buffer = (char *)malloc(sizeof(char)*TAM2);

			buffer = LeerArchivo(directorioActual);
	
			strcat(superbuffer, buffer);

			if (i != m-1)
				strcat(superbuffer, "\n\n");

   			free(buffer);
		}

		else {
			printf(" No es un archivo regular\n");
			exit(-1);
		}

		free(texto);
		free(directorioActual);
	}

	return(contArchivosProc);
}

/* EscribirPipes
* Procedimiento donde los procesos hijos escriben en los pipes.
* fd: pipe para la comunicación de procesos
* superbuffer: buffer donde se guardarán los archivos correspondientes 
* a un hijo
*/
void EscribirPipes(int fd[], char *superbuffer) {

 	close(fd[0]); /* Cerramos la lectura del pipe */
    write(fd[1], superbuffer, (strlen(superbuffer)));
}

/* LeerPipes
* Procedimiento donde el proceso padre lee del pipe.
* fd: arreglo de pipes
* salida: archivo donde el proceso padre escribirá todos los archivos de textos
* leídos por los procesos hijos 
*/
void LeerPipes(int fd[], char *salida) {

	close(fd[1]); /* Cerramos la escritura del pipe */

	char *bufferRead;
	int countbytes;
				
	bufferRead = (char *)malloc(sizeof(char)*TAM2);
    countbytes = read(fd[0], bufferRead, sizeof(bufferRead)*TAM2);

    printf("%s\n", bufferRead);
    printf("\nentro en leerPipes con %d\n", countbytes);

    EscribirArchivo(salida, bufferRead);

    free(bufferRead);
}

/* LeerArchivo
* Procedimiento donde los procesos hijos leen de los archivos de texto.
* directorioActual: directorio dessde donde los procesos hijos van a leer sus
* respectivos archivos de texto
* retorna un buffer 
*/
char *LeerArchivo(char *directorioActual) {

	FILE *fp;

	char *buf, *buf2; 
 	buf = (char *)malloc(sizeof(char)*TAM2);
 	buf2 = (char *)malloc(sizeof(char)*TAM2);

	fp = fopen(directorioActual, "r");
 
 	if (fp == NULL)
 		exit(1);

 	strcpy(buf2, "");
 
 	while (fgets(buf,TAM2,fp) != NULL)
 	{
 		strcat(buf2, buf);
 	}

	fclose(fp);
	free(buf);

	return buf2;
}

/* EscribirArchivo
* Procedimiento donde el proceso padre escribe en el archivo
* final de texto.
* salida: archivo donde se encuentra todo el archivo final creado por el proceso
* padre
* bufferRead: buffer que guardará todos los textos de todos los archivos
* leídos
*/
void EscribirArchivo(char *salida, char *bufferRead) {

	FILE *fp;
	fp = fopen(salida,"w");

	fprintf(fp, bufferRead);

	fclose(fp);
}
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
* retorna el arreglo ordenado de menor a mayor
*/ 
int *secuenciaRandom(int tamSecuencia, int randMax) {
	/* Utilizando el algoritmo Floyd para evitar números repetidos */
	unsigned char utilizado[randMax];
	memset(utilizado, 0, randMax * sizeof(unsigned char)); /* flags */ 

	int in, im;
	int *arreglo = malloc(sizeof(int) * tamSecuencia); 
	im = 0;

	/* Se inicializa la semilla del random con time() */
	srand(time(NULL));

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

<<<<<<< HEAD
/* AccesoCarpetas
* Accede a las carpetas correspondientes para hacer la verificación de si son 
* directorios o no.
* dir: directorio en el que se hará acceso para lectura de carpetas y archivos
* n: cantidad de elementos a recorrer en el arregloDirectorios
* m: cantidad de elementos a recorrer en el arregloTextos
* arregloDirectorios: arreglo que contiene cada uno de los números que 
* representan las carpetas a los que accesará cada uno de los procesos hijos
* arregloTextos: arreglo que contiene cada uno de los números que representan 
* los archivos a los que accesará cada uno de los procesos hijos
*/ 
void AccesoCarpetas(DIR *dir, int n, int m, int *arregloDirectorios, int *arregloTextos, int argc, char *cadena) {
=======
void AccesoCarpetas(DIR *dir, int n, int m, int j, int *arregloDirectorios, int *arregloTextos, int argc, char *cadena) {
>>>>>>> origin/developpeurs

	struct stat buffer; 		//Buffer con la informacion de la entrada
	struct dirent *direntd;
	struct dirent *direntd2;
	direntd = readdir(dir);
	int tam, rpta;
	tam = (unsigned) strlen(dir);

	rpta = *(arregloDirectorios + j);

	char *texto, *slash, *nombre, *directorioPrin;
	DIR *dir2;

	texto = (char *)malloc(sizeof(char)*TAM);
	nombre = (char *)malloc(sizeof(char)*TAM);
	directorioPrin = (char *)malloc(sizeof(char)*tam);

	sprintf(texto, "%d", rpta);

	if (argc == 6) {
		strcpy(directorioPrin, cadena);
		strcpy(nombre, directorioPrin);
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

	if (stat(nombre, &buffer) != 0) {
		printf(" No se pudo obtener la informacion de la carpeta %s\n", nombre);
		perror(" El error fue el siguiente ");
    	exit(-1);	
	}
	else if (S_ISDIR(buffer.st_mode)) {
		printf(" Es un directorio\n\n");
	}

	if ( (dir2 = opendir(texto)) == NULL) {

		perror(" No se puede abrir el directorio ya que no existe 3");
		exit(1);
	}
	else {
		//printf(" El directorio actual es %s\n", texto);
	}

	direntd2 = readdir(dir2);

	printf("Antes de AccesoArchivos\n");
	AccesoArchivos(dir2, m, arregloTextos, nombre);
	printf("Despues de AccesoArchivos\n");

	free(directorioPrin);
	free(texto);
	free(nombre);
	closedir(dir2);

}

void AccesoArchivos(DIR *dir2, int m, int *arregloTextos, char *nombre) {
	
	int i,rpta,tam2;
	struct stat buffer2; 		//Buffer con la informacion de la entrada
	char *texto, *directorioActual;
	tam2 = (unsigned) strlen(dir2);

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

		if (stat(directorioActual, &buffer2) != 0) {
			printf(" No se pudo obtener la informacion del archivo %s\n", directorioActual);
			perror(" El error fue el siguiente ");
			exit(-1);	
		}

		else if (S_ISREG(buffer2.st_mode)) {
			printf(" Es un archivo regular\n");
		}

		EscribirPipes(arregloPipes, directorioActual);
		free(texto);
		free(directorioActual);
	}
	
}

/* EscribirPipes
* Procedimiento donde los procesos hijos escriben en los pipes.
*/
void EscribirPipes(int *fd, char *directorioActual) {

	char *buffer; 
 	buffer = (char *)malloc(sizeof(char)*TAM);

    close(fd[0]); /* Cerramos la lectura del pipe */

    buffer = LeerArchivo(directorioActual, buffer);

    write(fd[1], buffer, strlen(buffer));
    close(fd[1]);

}

/* LeerPipes
* Procedimiento donde el proceso padre lee del pipe.
*/
void LeerPipes(int *fd, char *salida) {

    close(fd[1]); /* Cerramos la escritura del pipe */

    EscribirArchivo(salida);
    read(fd[0], buffer, SIZE)
    // while((readbytes=read(p[0], buffer, SIZE)) > 0) {
    //     //fprintf(archivo1, "%s",buffer);
    //     fwrite(buffer, 1, readbytes,archivo1);
    // }
    fclose(archivo1); 
    close(fd[0]);
}

/* LeerArchivo
* Procedimiento donde los procesos hijos leen de los archivos.
* de texto
*/
char *LeerArchivo(char *directorioActual, char *buffer) {

	FILE *fp;
	fp = fopen(directorioActual, "r");
 
 	if (fp == NULL)
 		exit(1);
 
 	while (feof(fp) == 0)
 	{
 		fgets(buffer,TAM,fp);
 		printf("%s",buffer);
 	}

	fclose(fp);

	return buffer;
}

/* EscribirArchivo
* Procedimiento donde el proceso padre escribe en el archivo
* final de texto.
*/
void EscribirArchivo(char *salida) {

	fp = fopen(salida,"w");

	fclose(fp);
}
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

	struct stat buffer; 		//Buffer con la informacion de la entrada
	struct dirent *direntd;
	struct dirent *direntd2;
	direntd = readdir(dir);
	int i,j, tam, rpta;
	tam = (unsigned) strlen(dir);

	for (i = 0; i < n; i++) {

		rpta = *(arregloDirectorios + i);

		char *texto, *slash, *nombre, *directorioPrin;
		DIR *dir2;

		texto = (char *)malloc(sizeof(char)*TAM);
		slash = (char *)malloc(sizeof(char)*TAM);
		nombre = (char *)malloc(sizeof(char)*TAM);
		directorioPrin = (char *)malloc(sizeof(char)*tam);

		slash = "/";
		sprintf(texto, "%d", rpta);

		/* Leemos las entradas del direntd */

		// while ( (direntd = readdir(dir) ) != NULL) {
	 	//   		printf("%d\t%d\t%d\t%s\n", direntd->d_ino, direntd->d_off, direntd->d_reclen, direntd->d_name);
	 	//  	}

		if (argc == 6) {
			directorioPrin = cadena;
			strcpy(nombre, directorioPrin);
			strcat(nombre, texto);
			//printf(nombre);	
		}
		else if (argc == 4) {
			getcwd(directorioPrin, TAM);
			strcpy(nombre, directorioPrin);
			strcat(nombre, slash);
			strcat(nombre, texto);
			//printf(nombre);
		}

		j = 0;
		j = stat(nombre, &buffer);

		if (j != 0) {
			printf(" No se pudo obtener la informacion de la carpeta %s\n", nombre);
			perror(" El error fue el siguiente ");
	    	exit(-1);	
		}
		else if (S_ISDIR(buffer.st_mode)) {
			//printf(" Es un directorio ");
		}

	if ( (dir2 = opendir(texto)) == NULL) {

		perror(" No se puede abrir el directorio ya que no existe 3");
		exit(1);
	}
	else {
		//printf(" El directorio actual es %s\n", texto);
	}

	 /* Leemos las entradas del direntd */
	
	direntd2 = readdir(dir2);

	// while ( (direntd2 = readdir(dir2) ) != NULL) {
	//  	printf("%d\t%d\t%d\t%s\n", direntd2->d_ino, direntd2->d_off, direntd2->d_reclen, direntd2->d_name);
	// }
	AccesoArchivos(dir2, m, arregloTextos, nombre, slash);
	free(directorioPrin);
	free(texto);
	}
}

void AccesoArchivos(DIR *dir2, int m, int *arregloTextos, char *nombre, char *slash) {

	int i,j,rpta,tam2;
	struct stat buffer2; 		//Buffer con la informacion de la entrada
	char *texto, directorioActual;
	tam2 = (unsigned) strlen(dir2);

	texto = (char *)malloc(sizeof(char)*TAM);
	directorioActual = (char *)malloc(sizeof(char)*tam2);

	for (i = 0; i < m; i++) {

		rpta = *(arregloTextos + i);

		sprintf(texto, "%d", rpta);

		directorioActual = nombre;
		strcat(directorioActual, slash);
		strcat(directorioActual, texto);
		strcat(directorioActual,"\0");
		printf(directorioActual);

		if (stat(directorioActual, &buffer2) != 0) {
			printf(" No se pudo obtener la informacion del archivo %s\n", directorioActual);
			perror(" El error fue el siguiente ");
			exit(-1);	
		}

		else if (S_ISREG(buffer2.st_mode)) {
			printf(" Es un archivo regular ");
		}

	}

	free(texto);
	free(directorioActual);
	free(slash);
	free(nombre);
	closedir(dir2);
}
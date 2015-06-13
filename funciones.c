/* 
 * Archivo: funciones.c
 * Este archivo contiene las funciones necesarias para la implementación del
 * problema planteado en el proyecto.
 *
 * Autores: Carlos Plantijn # Carnet 10-10572
 *  		Meggie Sanchez  # Carnet 11-10939
 */

#include "funciones.h"

/* Comparador de enteros */
int cmpfunc(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

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

void AccesoCarpetas(DIR *dir, int n, int m, int *arregloDirectorios, int argc, char *cadena) {

	struct stat buffer; 		//Buffer con la informacion de la entrada
	struct dirent *direntd;
	struct dirent *direntd2;
	direntd = readdir(dir);
	int i,j, tam;
	int rpta;
	tam = (unsigned) strlen(dir);

	for (i = 0; i < n; i++) {
		rpta = *(arregloDirectorios + i);
		//printf("%d", rpta);

		char *texto, *direntdName, *slash, *nombre, *directorioPrin;
		DIR *dir2;

		texto = (char *)malloc(sizeof(char)*TAM);
		//direntdName = (char *)malloc(sizeof(char)*TAM);
		slash = (char *)malloc(sizeof(char)*TAM);
		nombre = (char *)malloc(sizeof(char)*TAM);
		directorioPrin = (char *)malloc(sizeof(char)*tam);

		sprintf(texto, "%d", rpta);
		//printf("%s", texto);

		/* Leemos las entradas del direntd */

		// while ( (direntd = readdir(dir) ) != NULL) {
	 	//   		printf("%d\t%d\t%d\t%s\n", direntd->d_ino, direntd->d_off, direntd->d_reclen, direntd->d_name);
	 	//  	}

		//direntdName = texto;
		//printf("%s", direntd->d_name);
		slash = "/";
		//printf(direntdName);

		if (argc == 6) {
			directorioPrin = cadena;
			strcpy(nombre, directorioPrin);
			strcat(nombre, texto);
			strcat(nombre,"\0");
			printf(nombre);			
		}
		else if (argc == 4) {
			getcwd(directorioPrin, TAM);
			strcpy(nombre, directorioPrin);
			strcat(nombre, slash);
			strcat(nombre, texto);
			strcat(nombre,"\0");
			printf(nombre);	
		}

		j = 0;
		j = stat(nombre, &buffer);

		if (j != 0) {
			printf( "no se pudo obtener la informacion de %s\n", nombre);
			perror("El error fue el siguiente ");
	    	exit(-1);	
		}

	if ( (dir2 = opendir(texto)) == NULL) {

		perror(" No se puede abrir el directorio ya que no existe 3");
		exit(1);
	}
	else {
		printf(" El directorio actual es %s\n", texto);
		direntd2 = readdir(dir2);
	}

	 /* Leemos las entradas del direntd */
	
		// while ( (direntd = readdir(dir2) ) != NULL) {
		//  	printf("%d\t%d\t%d\t%s\n", direntd->d_ino, direntd->d_off, direntd->d_reclen, direntd->d_name);
		// }

	closedir(dir2);

	// free(slash);
	// free(nombre);
	// free(texto);
	// free(direntdName);
	}
}
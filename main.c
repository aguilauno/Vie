/* 
 * Archivo: main.c
 * Este archivo contiene el programa principal.
 *
 * Autores: Carlos Plantjin # Carnet 10-10572
 *  		Meggie Sanchez  # Carnet 11-10939
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

 /* Programa principal */

int main(int argc, char *argv[]) {

	char *directorio, *salida;
	int n, m;

	DIR *dir;

	salida = (char *)malloc(sizeof(char)*50);
	directorio = (char *)malloc(sizeof(char)*50);

	if (argc == 6) { /* Cuando se colocan todos los parámetros completos */

		directorio = strdup(argv[1]);

		DIR *opendir(directorio);

		if ((dir = opendir(argv[1])) == NULL) {

			perror("opendir");
			return 0;
		}

		n = atoi(argv[2]); /* Valor n que el padre debe considerar */

		if (n >= 10) {

			printf(" El parámetro n debe ser menor que 10 ");
			exit(1);
		}

		m = atoi(argv[3]); /* Valor m que los hijos deben considerar */

		if (m >= 20) {

			printf(" El parámetro n debe ser menor que 20 ");
			exit(1);
		}

		salida = strdup(argv[4]);

	}

//	else if (argc == 5) { /* Cuando no se coloca el directorio, se toma el directorio actual por default */

//	}

	else if (argc > 6 || argc < 5) { /* Cuando no se indican los parámetros necesarios */

		printf("Error, no se indican los parámetros necesarios.\n");
    	exit(1);

	}


} 
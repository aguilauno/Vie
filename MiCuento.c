/* 
 * Archivo: MiCuento.c
 * Este archivo contiene el programa principal.
 *
 * Autores: Carlos Plantijn # Carnet 10-10572
 *  		Meggie Sanchez  # Carnet 11-10939
 */

#include "funciones.h"

 /* Programa principal */

int main(int argc, char *argv[]) {

	char *salida, *cadena;
	int i, n, m;

	DIR *dir;

	cadena = (char *)malloc(sizeof(char)*TAM);
	salida = (char *)malloc(sizeof(char)*TAM);

	if ((argc == 6) || (argc == 4)) { 
		
		if (argc == 6) {
			/* Cuando se colocan todos los parámetros completos */
			i = 2;
			if ((dir = opendir(argv[i++])) == NULL) {
				perror("opendir no se pudo realizar");
				exit(1);
			}
		}

		else if (argc == 4) { 
			/* Cuando no se coloca el directorio, se toma el directorio actual por default */
			i = 1;
			if ((dir = opendir(".")) == NULL) {
				error(" No se puede abrir el directorio ");
				exit(1);
			}
		}

		n = atoi(argv[i++]); /* Valor n que el padre debe considerar */

		if ((n > 10) || (n < 1)) {
			printf(" El parámetro n debe estar entre 1 y 10 \n");
			exit(1);
		}

		m = atoi(argv[i++]); /* Valor m que los hijos deben considerar */

		if ((m > 20) || (m < 1)) {
			printf(" El parámetro m debe estar entre 1 y 20 \n");
			exit(1);
		}

		int *arregloDirectorios;
		int *arregloTextos;
		
		arregloDirectorios = secuenciaRandom(n, MAX_N);
		arregloTextos      = secuenciaRandom(m, MAX_M);

		/* Prueba de manejo de apuntadores de arreglos */
		// int j;
		// printf("\n\n");
		// for (j = 0; j < n; ++j)
		// 	printf("%d ", *(arregloDirectorios + j));
		// printf("\n");
		// for (j = 0; j < m; ++j)
		// 	printf("%d ", *(arregloTextos + j));
		// printf("\n\n\n");

		/* Crear n procesos hijos y cada uno toma control
		 * de la carpeta que le tocó aleatoriamente */

		/* Luego cada proceso hijo genera m números aleatorios [1..20] para
		 * seleccionar de sus textos cuales va a usar en el cuento */

		AccesoCarpetas(dir);
		salida = strdup(argv[i]);
		closedir(dir);		
	}

	else if (argc > 6 || argc < 4) { /* Cuando no se indican los parámetros necesarios */

		printf("Error, no se indican los parámetros necesarios.\n");
    	exit(1);
	}

	return 0;
} 

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

	/* Inicializamos el pipe */
	int fd[2];
	pipe(fd);

	char *salida, *cadena;
	int i, n, m, j, status;

	DIR *dir;

	cadena = (char *)malloc(sizeof(char)*TAM);
	salida = (char *)malloc(sizeof(char)*TAM);

	if ((argc == 6) || (argc == 4)) { 
		
		if (argc == 6) {
			/* Cuando se colocan todos los parámetros completos */
			i = 2;
			if ((dir = opendir(argv[i++])) == NULL) {
				perror(" No se puede abrir el directorio ya que no existe 1");
				exit(1);
			}
			cadena = argv[2];
		}

		else if (argc == 4) { 
			/* Cuando no se coloca el directorio, se toma el directorio actual por default */
			i = 1;
			if ((dir = opendir(".")) == NULL) {
				error(" No se puede abrir el directorio ya que no existe 2");
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
		
		arregloDirectorios = secuenciaRandom(n, MAX_N);
		

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

		/* Arreglo de procesos hijos */  
  		pid_t hijos[n];

  		/* Ciclo generador de los procesos hijos */
  		for (j = 0; j < n; ++j) {
	
			hijos[j]=fork();

			if (hijos[j] == -1) {
			  printf("Hubo un error al crear un hijo, el programa se detendra\n");
			  exit(-1);
			}

		    if (hijos[j] == 0) {
				/* Luego cada proceso hijo genera m números aleatorios [1..20] para
				 * seleccionar de sus textos cuales va a usar en el cuento */
		    	int *arregloTextos;
		    	arregloTextos = secuenciaRandom(m, MAX_M);

		    	AccesoCarpetas(dir, n, m, arregloDirectorios, arregloTextos, argc, cadena);
				salida = strdup(argv[i]);
				closedir(dir);

			}
  		}

  		/* Ciclo que espera por los procesos hijos */
		for (j = 0; j < n; ++j) {
			waitpid(hijos[j], &status, 0);
			status = WEXITSTATUS(status);		
		}		

	}

	else if (argc > 6 || argc < 4) { /* Cuando no se indican los parámetros necesarios */

		printf(" Error, no se indican los parámetros necesarios. \n");
    	exit(1);
	}

	return 0;
} 

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
	int i, n, m, j, status;

	DIR *dir; /* Directorio principal a abrir */

	if ((argc == 6) || (argc == 4)) { /* Verificación de parámetros */
		
		if (argc == 6) {
			/* Cuando se colocan todos los parámetros completos */
			i = 2;
			if ((dir = opendir(argv[i++])) == NULL) {
				perror(" No se puede abrir el directorio ya que no existe ");
				exit(1);
			}
			cadena = argv[2];
		}

		else if (argc == 4) { 
			/* Cuando no se coloca el directorio, se toma el directorio actual por default */
			i = 1;
			if ((dir = opendir(".")) == NULL) {
				error(" No se puede abrir el directorio ya que no existe ");
				exit(1);
			}
		}

		n = atoi(argv[i++]); /* Valor n que el padre debe considerar para saber sus hijos */

		if ((n > 10) || (n < 1)) {
			printf(" El parámetro n debe estar entre 1 y 10 \n");
			exit(1);
		}

		m = atoi(argv[i++]); /* Valor m que los hijos deben considerar */

		if ((m > 20) || (m < 1)) {
			printf(" El parámetro m debe estar entre 1 y 20 \n");
			exit(1);
		}

		int *arregloDirectorios; /* Arreglo de cantidad n para números 
									aleatorios para el acceso a carpetas */

		salida = strdup(argv[i]); /* Obtenemos el archivo de salida */
		
		arregloDirectorios = secuenciaRandom(n, MAX_N, 0);

		/* Inicializamos el pipe */
		int fd[2];

		/* Arreglo de procesos hijos */  
  		pid_t hijos[n];

  		pipe(fd);

  		char *superbuffer;
 		superbuffer = (char *)malloc(sizeof(char)*TAM2+64);

 		int contArchivosProc;

  		/* Crear n procesos hijos y cada uno toma control de la carpeta que le 
  		   tocó aleatoriamente. Ciclo generador de los procesos hijos */
  		for (j = 0; j < n; ++j) {

			if ((hijos[j] = fork()) == -1) {
			  printf(" Hubo un error al crear un hijo, el programa se detendrá \n");
			  exit(-1);
			}

		    if (hijos[j] == 0) {

				/* Luego cada proceso hijo genera m números aleatorios [1..20] para
				 * seleccionar de sus textos cuales va a usar en el cuento */
		    	int *arregloTextos;
		    	arregloTextos = secuenciaRandom(m, MAX_M, getpid());
		    	//printf("Soy el hijo con pid %d, iteracion:%d\n", getpid(), j);

		    	contArchivosProc = AccesoCarpetas(dir, n, m, j, arregloDirectorios, arregloTextos, argc, cadena, fd, superbuffer);

		    	if (j != n-1)
					strcat(superbuffer, "\n\n");
		    	
		    	EscribirPipes(fd, superbuffer);
		    	close(fd[1]); /* Cerramos la escritura del pipe */

		    	free(superbuffer);

		    	printf("CONTADOR DEL EXIT %d\n", contArchivosProc);

		    	exit(contArchivosProc);
			}
/*			else {
				printf("Soy el Padre con ID= %ld, mi hijo es %ld\n",(long)getpid(),hijos[j]);
			}*/
  		}

  		/* Ciclo que espera por los procesos hijos */
		for (j = 0; j < n; ++j) {
			waitpid(hijos[j], &status, 0);
			status = WEXITSTATUS(status);	
		}	

		LeerPipes(fd, salida);
		close(fd[0]); /* Cerramos la lectura del pipe */
	}		

	else if (argc > 6 || argc < 4) { /* Cuando no se indican los parámetros necesarios */

		printf(" Error, no se indican los parámetros necesarios. \n");
    	exit(1);
	}

	closedir(dir);

	return 0;
} 

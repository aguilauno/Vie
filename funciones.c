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

void AccesoCarpetas(DIR *dir) {

	struct dirent *direntd;

	 /* Leemos las entradas del direntd */
	
	// while ( (direntd = readdir(dir) ) != NULL) {
	// 	printf("%d\t%d\t%d\t%s\n", direntd->d_ino, direntd->d_off, direntd->d_reclen, direntd->d_name);
	// }
	
	direntd = readdir(dir);
	int array[] = {1, 3, 5, 8};
	int i;
	int n = 4;

	for (i = 1; i <= n; i++) {

		char *texto;

		texto = (char *)malloc(sizeof(char)*TAM);

		sprintf(texto, "%d", i);
		direntd = readdir(dir);

		DIR *dir2;

	if ( (dir2 = opendir(texto)) == NULL) {

		perror(" opendir no se pudo realizar ya que dicho directorio no existe ");
		exit(1);
	}

	dir2 = opendir(texto);

	printf("El directorio actual es %s\n", texto);

	 /* Leemos las entradas del direntd */
	
		while ( (direntd = readdir(dir2) ) != NULL) {
		 	printf("%d\t%d\t%d\t%s\n", direntd->d_ino, direntd->d_off, direntd->d_reclen, direntd->d_name);
		}

		closedir(dir2);
	}
}
/* 
 * Archivo: funciones.h
 * Este archivo contiene las funciones necesarias para la implementación del
 * problema planteado en el proyecto.
 *
 * Autores: Carlos Plantijn # Carnet 10-10572
 *  		Meggie Sanchez  # Carnet 11-10939
 */

/* Librerías utilizadas */
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dir.h>
#include <time.h>
#include <assert.h>


/* Constantes */
#define TAM   80 /* */
#define MAX_N 10 /* Valor máximo para el rango del número aleatorio n */
#define MAX_M 20 /* Valor máximo para el rango del número aleatorio m */


/* Funciones */

/* Comparador de enteros */
int cmpfunc(const void *a, const void *b);
/* Genera el apuntador a un arreglo de números aleatorios */
int *secuenciaRandom(int tamSecuencia, int randMax);
/* */
void AccesoCarpetas(DIR *dir);
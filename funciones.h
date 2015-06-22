/* 
 * Archivo: funciones.h
 * Este archivo contiene las declaraciones de las funciones necesarias para 
 * la implementación del problema planteado en el proyecto. Posee además todas
 * las librerías y constantes necesarias.
 *
 * Autores: Carlos Plantijn # Carnet 10-10572
 *  		Meggie Sanchez  # Carnet 11-10939
 */

/* Librerías utilizadas */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <assert.h>

/* Constantes */
#define TAM   200 /* Valor arbitrario para definir un tamaño para strings */
#define TAM2  1048576 /* Valor arbitrario para definir un tamaño para buffers */
#define MAX_N 10  /* Valor máximo para el rango del número aleatorio n */
#define MAX_M 20  /* Valor máximo para el rango del número aleatorio m */

/* Funciones */

/* Comparador de enteros */
int cmpfunc(const void *a, const void *b);
/* Genera el apuntador a un arreglo de números aleatorios */
int *secuenciaRandom(int tamSecuencia, int randMax, int pidHijo);
/* Procedimiento para acceder a las carpetas necesarias */
int AccesoCarpetas(int n, int m, int j, int *arregloDirectorios, int *arregloTextos, int argc, char *cadena, int fd[], char *superbuffer);
/* Procedimiento para acceder a los archivos necesarios */
int AccesoArchivos(int m, int *arregloTextos, char *nombre, int fd[], char *superbuffer);
/* Procedimiento para que el proceso padre lea de los pipes */
void LeerPipes(int fd[], char *salida);
/* Procedimiento para que los procesos hijos escriban en los pipes */
void EscribirPipes(int fd[], char *superbuffer);
/* Funcion donde los procesos hijos leen de los archivos */
char *LeerArchivo(char *directorioActual);
/* Procedimiento donde el proceso padre escribe el texto final en salida */
void EscribirArchivo(char *salida, char *bufferRead);

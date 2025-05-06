/*****************************************************************************************
Materia: Sistemas Operativos
#     Fichero: mmInterfazPosix.h
#     Autor: John Jairo Corredor
#     Editores: Roberth Santiago Mendez, Gabriel Jaramillo Cuberos, Guden Sebastian Silva, Viviana Gomez Leon, Luz Adriana Salazar
#     Descripcion: Fichero para la ejecución de ejecutables
*****************************************************************************************/

#include <stdio.h>       // Librería estándar de entrada y salida
#include <pthread.h>     // Librería para manejo de hilos POSIX
#include <unistd.h>      // Librería para llamadas al sistema
#include <stdlib.h>      // Librería para uso de funciones como malloc, atoi, rand
#include <time.h>        // Librería para manejo de tiempo (semillas aleatorias)
#include <sys/time.h>    // Librería para medir tiempo en microsegundos con timeval

#define DATA_SIZE (1024*1024*64*3) // Tamaño total del bloque de memoria compartida

extern pthread_mutex_t MM_mutex;          // Mutex para sincronización entre hilos
extern double MEM_CHUNK[DATA_SIZE];// Bloque de memoria compartida para las matrices
extern double *mA, *mB, *mC;              // Punteros a las matrices A, B y C

// Variables para almacenar tiempo de inicio y fin de la medición
extern struct timeval inicio, fin;

// Estructura para enviar parámetros a cada hilo
struct parametros{
	int nH;   // Número total de hilos
	int idH;  // ID del hilo (índice)
	int N;    // Tamaño de la matriz
};

/*
 * Función que registra el tiempo de inicio para medir duración de ejecución
 */
void InicioMuestra();

/*
 * Función que registra el tiempo final, calcula la diferencia y muestra el tiempo total en microsegundos
 */
void FinMuestra();

/*
 * Función que inicializa las matrices A y B con valores aleatorios entre 0 y 9
 * y la matriz C en ceros
 * Parámetro:
 *   - SZ: tamaño de la matriz
 */
void iniMatrix(int SZ);

/*
 * Función que imprime una matriz si su tamaño es menor a 12
 * Parámetros:
 *   - sz: tamaño de la matriz (matriz cuadrada sz x sz)
 *   - matriz: puntero a la matriz que se quiere imprimir
 */
void impMatrix(int sz, double *matriz);

/*
 * Función que ejecuta cada hilo para realizar la multiplicación parcial de matrices
 * Parámetro:
 *   - variables: puntero genérico que se castea a struct parametros con info del hilo
 */
void *multiMatrix(void *variables);
/*****************************************************************************************
Materia: Sistemas Operativos
#     Fichero: mmInterfazFork.h
#     Autor: John Jairo Corredor
#     Editores: Roberth Santiago Mendez, Gabriel Jaramillo Cuberos, Guden Sebastian Silva, Viviana Gomez Leon, Luz Adriana Salazar
#     Descripcion: Fichero para la ejecución de ejecutables
*****************************************************************************************/

#ifndef _MMCLASICA_FORK_H_
#define _MMCLASICA_FORK_H_

#include <stdio.h>		// Librería estándar de entrada y salida
#include <stdlib.h>		// Librería para uso de funciones como malloc, atoi, rand
#include <unistd.h>		// Librería para llamadas al sistema
#include <sys/wait.h>	// Librería para manejar procesos hijos
#include <sys/time.h>	// Librería para medir tiempo en microsegundos con timeval
#include <time.h>		// Librería para manejo de tiempo (semillas aleatorias)

/*
 * Función que registra el tiempo de inicio para luego medir el
 * tiempo total de la ejecución.
 */
void InicioMuestra();

/*
 * Función que registra el tiempo de finalización, calcula la diferencia
 * con el tiempo inicial y muestra el tiempo total de ejecución.
 */
void FinMuestra();

/*
 * Función que realiza la multiplicación de matrices entre mA y mB, y almacena el
 * resultado en mC. Cada proceso trabaja sobre un rango de filas determinado por filaI y filaF.
 * Parámetros:
 *  - mA: puntero a la matriz A
 *  - mB: puntero a la matriz B
 *  - mC: puntero a la matriz resultado C
 *  - D: dimensión de las matrices cuadradas
 *  - filaI: fila inicial a procesar
 *  - filaF: fila final a procesar
 */
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

/*
 * Función que imprime el contenido de la matriz si la dimensión es menor a 9.
 * Parámetros:
 *  - matrix: puntero a la matriz a imprimir
 *  - D: dimensión de la matriz cuadrada
 */
void impMatrix(double *matrix, int D);

/*
 * Función que inicializa las matrices A y B con valores aleatorios entre 0 y 9.
 * Parámetros:
 *  - mA: puntero a la matriz A
 *  - mB: puntero a la matriz B
 *  - D: dimensión de las matrices cuadradas
 */
void iniMatrix(double *mA, double *mB, int D);









#endif
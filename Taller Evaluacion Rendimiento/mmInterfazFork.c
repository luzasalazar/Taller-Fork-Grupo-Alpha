/*****************************************************************************************
Materia: Sistemas Operativos
#     Fichero: mmInterfazFork.c
#     Autor: John Jairo Corredor
#     Editores: Roberth Santiago Mendez, Gabriel Jaramillo Cuberos, Guden Sebastian Silva, Viviana Gomez Leon, Luz Adriana Salazar
#     Descripcion: Fichero para la ejecución de ejecutables
*****************************************************************************************/

#include "mmInterfazFork.h"

/*
 * Variables globales utilizadas para almacenar el tiempo de inicio y fin
 * de ejecución entre dos puntos del programa.
 */
struct timeval inicio, fin;

void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}

void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}

void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
	double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) {
        for (int j = 0; j < D; j++) {
			Suma = 0;
			pA = mA+i*D;
			pB = mB+j;
            for (int k = 0; k < D; k++, pA++, pB+=D) {
				Suma += *pA * *pB;	
            }
			mC[i*D+j] = Suma;
        }
    }
}

void impMatrix(double *matrix, int D) {
	if (D < 9) {
    	printf("\nImpresión	...\n");
    	for (int i = 0; i < D*D; i++, matrix++) {
			if(i%D==0) 
				printf("\n");
            printf(" %f ", *matrix);
        }
        printf("\n ");
    }
}

void iniMatrix(double *mA, double *mB, int D){
	for (int i = 0; i < D*D; i++, mA++, mB++){
            *mA = rand() % 10; 
            *mB = rand() % 10; 
        }
}
/*****************************************************************************************
Materia: Sistemas Operativos
#     Fichero: mmInterfazPosix.c
#     Autor: John Jairo Corredor
#     Editores: Roberth Santiago Mendez, Gabriel Jaramillo Cuberos, Guden Sebastian Silva, Viviana Gomez Leon, Luz Adriana Salazar
#     Descripcion: Fichero para la ejecución de ejecutables
*****************************************************************************************/

#include "mmInterfazPosix.h" // Incluye la interfaz de POSIX para la multiplicación de matrices

pthread_mutex_t MM_mutex;          
double MEM_CHUNK[DATA_SIZE];
double *mA, *mB, *mC;

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

void iniMatrix(int SZ){ 
	for(int i = 0; i < SZ*SZ; i++){
			mA[i] = rand() % 10; 
			mB[i] = rand() % 10;
			mC[i] = 0; 
		}	
}

void impMatrix(int sz, double *matriz){
	if(sz < 12){
    	for(int i = 0; i < sz*sz; i++){
     		if(i%sz==0) printf("\n");
            printf(" %.3f ", matriz[i]);
		}	
    	printf("\n>-------------------->\n");
	}
}

void *multiMatrix(void *variables){
	struct parametros *data = (struct parametros *)variables;
	
	int idH = data->idH;
	int nH  = data->nH;
	int N   = data->N;
	int ini = (N/nH)*idH;         // Fila inicial que procesa este hilo
	int fin = (N/nH)*(idH+1);     // Fila final 

    for (int i = ini; i < fin; i++){
        for (int j = 0; j < N; j++){
			double *pA, *pB, sumaTemp = 0.0;
			pA = mA + (i*N);      // Apunta al inicio de la fila i en A
			pB = mB + j;          // Apunta a la columna j en B
            for (int k = 0; k < N; k++, pA++, pB+=N){
				sumaTemp += (*pA * *pB); // Multiplicación y acumulación
			}
			mC[i*N+j] = sumaTemp; // Asignación del valor en la matriz de resultado
		}
	}

	// Sección crítica protegida con mutex
	pthread_mutex_lock (&MM_mutex);
	pthread_mutex_unlock (&MM_mutex);
	pthread_exit(NULL);
    
}
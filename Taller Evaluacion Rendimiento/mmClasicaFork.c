/*****************************************************************************************
Materia: Sistemas Operativos
#     Fichero: Automatización para ejecuciones por lotes
#     Autor: John Jairo Corredor
#     Editores: Roberth Santiago Mendez, Gabriel Jaramillo Cuberos, Guden Sebastian Silva, Viviana Gomez Leon, Luz Adriana Salazar
#     Descripcion: Fichero para la ejecución de ejecutables
*****************************************************************************************/

#include "mmInterfazFork.h" // Librería personalizada para funciones de matrices

/*
 * Función principal en la que:
 * 1. Se verifica que se ingresen correctamente los argumentos (tamaño de matriz y número de procesos)
 * 2. Se inicializan tres matrices dinámicas (matA, matB, matC)
 * 3. Se llenan las matrices matA y matB con valores aleatorios
 * 4. Se imprimen las matrices si su tamaño es menor a 9
 * 5. Se divide el trabajo entre múltiples procesos usando fork()
 * 6. Cada proceso hijo realiza la multiplicación parcial de las matrices
 * 7. Cada proceso hijo imprime su resultado si el tamaño de la matriz es pequeño
 * 8. El proceso padre espera que todos los procesos hijos terminen
 * 9. Se mide e imprime el tiempo total de ejecución
 * 10. Se libera la memoria reservada
 */
int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("\n \t\tUse: $./nom_ejecutable Size Hilos \n");
		exit(1);
	}
	int N      = (int) atoi(argv[1]);
	int num_P  = (int) atoi(argv[2]);
    double *matA = (double *) calloc(N*N, sizeof(double));
    double *matB = (double *) calloc(N*N, sizeof(double));
    double *matC = (double *) calloc(N*N, sizeof(double));

    srand(time(0)); // Semilla para generación de números aleatorios
    
    iniMatrix(matA, matB, N);
    impMatrix(matA, N);
    impMatrix(matB, N);
    
    int rows_per_process = N/ num_P;

	InicioMuestra();
    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork();
        
        if (pid == 0) { // Proceso hijo
            int start_row = i * rows_per_process;
            int end_row = (i == num_P - 1) ? N : start_row + rows_per_process;
            
			multiMatrix(matA, matB, matC, N, start_row, end_row); 
            
			if(N<9){
            	// Imprimir la porción calculada por este hijo
           		printf("\nChild PID %d calculated rows %d to %d:\n", getpid(), start_row, end_row-1);
            	for (int r = start_row; r < end_row; r++) {
                	for (int c = 0; c < N; c++) {
                    	printf(" %f ", matC[N*r+c]);
                	}
                	printf("\n");
            	}
			}
            exit(0); // El proceso hijo termina luego de completar su tarea
        } else if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
    }
    
    // El padre espera que todos los hijos terminen
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }
  	
	FinMuestra(); 
 
	free(matA);
	free(matB);
	free(matC);

    return 0;
}

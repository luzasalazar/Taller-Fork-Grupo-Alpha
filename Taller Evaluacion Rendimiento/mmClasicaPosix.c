/*****************************************************************************************
Materia: Sistemas Operativos
#     Fichero: mmClasicaPosix.c
#     Autor: John Jairo Corredor
#     Editores: Roberth Santiago Mendez, Gabriel Jaramillo Cuberos, Guden Sebastian Silva, Viviana Gomez Leon, Luz Adriana Salazar
#     Descripcion: Fichero para la ejecución de ejecutables
*****************************************************************************************/

#include "mmInterfazPosix.h" // Incluye la interfaz de POSIX para la multiplicación de matrices

/*
 * Función principal que:
 * 1. Valida argumentos de entrada (tamaño y número de hilos)
 * 2. Reserva memoria e inicializa matrices
 * 3. Crea hilos para multiplicar matrices
 * 4. Mide el tiempo total
 * 5. Imprime resultados si el tamaño es pequeño
 */
int main(int argc, char *argv[]){
	if (argc < 3){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		exit(0);	
	}
    int SZ = atoi(argv[1]);        // Tamaño de la matriz (matrices cuadradas)
    int n_threads = atoi(argv[2]); // Número de hilos

    pthread_t p[n_threads];        // Arreglo de identificadores de hilos
    pthread_attr_t atrMM;          // Atributo para los hilos

	mA = MEM_CHUNK;                // Apuntadores a cada matriz dentro del bloque de memoria
	mB = mA + SZ*SZ;
	mC = mB + SZ*SZ;

	iniMatrix(SZ);                 // Inicialización de las matrices A y B
	impMatrix(SZ, mA);             // Impresión opcional de A
	impMatrix(SZ, mB);             // Impresión opcional de B

	InicioMuestra();               // Inicio del cronómetro

	pthread_mutex_init(&MM_mutex, NULL);             // Inicialización del mutex
	pthread_attr_init(&atrMM);                       // Inicialización de atributos del hilo
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Hilos unibles

    for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;             // ID del hilo
		datos->nH  = n_threads;     // Total de hilos
		datos->N   = SZ;            // Tamaño de la matriz
        pthread_create(&p[j], &atrMM, multiMatrix, (void *)datos); // Creación del hilo
	}

    for (int j=0; j<n_threads; j++)
        pthread_join(p[j], NULL);  // Esperar a que cada hilo termine

	FinMuestra();                  // Final del cronómetro y mostrar tiempo

	impMatrix(SZ, mC);             // Imprimir la matriz resultado si es pequeña

	pthread_attr_destroy(&atrMM);  // Liberar atributos de hilo
	pthread_mutex_destroy(&MM_mutex); // Destruir el mutex
	pthread_exit(NULL);            // Terminar hilo principal correctamente
	
}

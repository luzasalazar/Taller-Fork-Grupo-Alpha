/**************************************************************************************************
    Pontificia Universidad Javeriana
Asignatura: Sistemas Operativos
Autores: Roberth Mendez, Gabriel Jaramillo, Viviana Gómez, Luz Salazar, Guden Silva.
Fecha: Abril 2025
Temas: pipe, fork, procesos padre e hijos, uso de llamadas al sistema.
**************************************************************************************************/

#include <stdlib.h> //Libreria para memoria dinamica y funciones como malloc, free, exit, atoi.
#include <stdio.h> //Libreria para el uso de funciones de entrada y salida (E/S)
#include <unistd.h> //Libreria para el uso de llamadas al sistema (fork, pipe)
#include <sys/types.h> //Librearia para el uso de identificador de proceso (pid_t)
#include <sys/wait.h> //Libreria para el uso de la función wait()

/*
* Definición de estrucutra para un vector dinamico
* que permite almacenar datos de cualquier tipo.
*/
typedef struct vectorDinamico{
    int capacidad; //Capacidad maxima del vector
    int totalElementos; //Numero de elementos en el vector
    void **elementos; //Arreglo de apuntadores de tipo generico
} vectorDinamico;

//Definición de funciones para operaciones con el vector dinamico
void vectorInicio(vectorDinamico *V, int capacidadInicial);
void leerFichero(char *nombreArchivo, vectorDinamico *vector, int capacidadVector);
int sumarVector(vectorDinamico *vector);
void freeVector(vectorDinamico *vector);

/**
 * Función principal en la que:
 * 1. Se verifica argumentos de linea de comandos
 * 2. Se inicializa dos vectores dinamicos
 * 3. Se lee datos de dos archivos y los carga en sus respectivos vectores
 * 4. Se crea procesos hijos para calcular sumas parciales y totales
 * 5. Se utiliza pipes para comunicar resultados entre procesos
 * 6. Se muestra los resultados finales
 * 7. Se libera la memoria reservada para los vectores
 */
int main(int argc, char *argv[]) {

    //Verificación de que haya 5 argumentos (<Ejecutable> <N1> <archivo00> <N2> <archivo01>)
    if (argc != 5) {
        printf("Uso correcto: %s <N1> <archivo00> <N2> <archivo01>\n", argv[0]); //Estructura correcta para la ejecución
        return 1;
    }

    //Convertir los argumentos <N1> y <N2> a numeros enteros
    int n1 = atoi(argv[1]); // Capacidad para el primer vector dinamico
    int n2 = atoi(argv[3]); // Capacidad para el segundo vector dinamico


    vectorDinamico vector1; //Creación primer vector dinamico
    vectorInicio(&vector1, n1); //Inicializar primer vector dinamico

    vectorDinamico vector2; //Creación segundo vector dinamico
    vectorInicio(&vector2, n2); //Inicializar segundo vector dinamico

     //Cargar datos desde archivos a los vectores dinamicos
    leerFichero(argv[2], &vector1, n1); //Primer archivo se carga a vector1
    leerFichero(argv[4], &vector2, n2);//Segundo archivo se carga a vector2

    int pipefd[2]; //Crear el pipe para la comunicación entre procesos (leer y escribir)

    //Verificación de la creación correcta del pipe (si fallo retorna -1)
    if (pipe(pipefd) == -1) {
        perror("Error al crear el pipe");
        return 1;
    }

    //Creación de proceso hijo para calcular la suma de vector1
    // y asignación de su PID retornada por el fork (0)
    pid_t pidSumaA = fork();

    //Verificación de la creación correcta del hijo (si fallo retorna -1)
    if (pidSumaA < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    //Codigo a ejecutar por el hijo ( si es el hijo su PID es 0)
    if (pidSumaA == 0) {

        int sumaA = sumarVector(&vector1); //Llamada a función para la suma del vector1 y almacenar resultado
        close(pipefd[0]); // Cierra lectura

        write(pipefd[1], &sumaA, sizeof(int)); //Envía resultado de la suma al pipe
        close(pipefd[1]); // Cierra escritura

        exit(0);

    }

    wait(NULL); // Espera a que el proceso hijo de sumaA termine antes de continuar
    
    //Creación de proceso hijo para calcular la suma de vector2
    // y asignación de su PID retornada por el fork (0)
    pid_t pidSumaB = fork(); 

    //Verificación de la creación correcta del hijo (si fallo retorna -1)
    if (pidSumaB < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    //Codigo a ejecutar por el hijo ( si es el hijo su PID es 0)
    if (pidSumaB == 0) { 
        
        int sumaB = sumarVector(&vector2); //Llamada a función para la suma del vector2 y almacenar resultado
        close(pipefd[0]); // Cierra lectura

        write(pipefd[1], &sumaB, sizeof(int)); //Envía resultado de la suma al pipe
        close(pipefd[1]); // Cierra escritura

        exit(0);

    }

    wait(NULL); // Espera a que el proceso hijo de sumaB termine antes de continuar

    //Creación de proceso hijo para calcular la suma total de ambos vectores
    // y asignación de su PID retornada por el fork (0)
    pid_t pidSumaTotal = fork();

    //Verificación de la creación correcta del hijo (si fallo retorna -1)
    if (pidSumaTotal < 0) {
        perror("Error al crear el proceso hijo");
        return 1;
    }

    //Codigo a ejecutar por el hijo ( si es el hijo su PID es 0)
    if (pidSumaTotal == 0) {

        int sumaTotal = sumarVector(&vector1) + sumarVector(&vector2); //Calcular suma total y almacenar el resultado
        close(pipefd[0]); // Cierra lectura

        write(pipefd[1], &sumaTotal, sizeof(int)); // Envía resultado de la suma al pipe
        close(pipefd[1]); // Cierra escritura

        exit(0);

    }

    wait(NULL); // Espera a que el proceso hijo de sumaTotal termine antes de continuar
    
    
    int sumaTotal, sumaA, sumaB; // Proceso Padre lee los resultados de los procesos hijos
    close(pipefd[1]); // Cierra escritura

    //Lee los valores enviados por los procesos hijos
    read(pipefd[0], &sumaA, sizeof(int)); //Lee el resultado de la suma de vector1
    read(pipefd[0], &sumaB, sizeof(int)); //Lee el resultado de la suma de vector2
    read(pipefd[0], &sumaTotal, sizeof(int)); //Lee el resultado de la suma total
    close(pipefd[0]); // Cierra lectura

    //Imprime los resultados
    printf("Suma Total: %d\n", sumaTotal);
    printf("Suma A: %d\n", sumaA);
    printf("Suma B: %d\n", sumaB);

    //Libera la memoria reservada para los vectores
    freeVector(&vector1); //Libera memoria del vector1
    freeVector(&vector2); //Libera memoria del vector2

    return 0;

}


/*
 * Inicializa un vector dinámico con la capacidad especificada
 * @param apuntador al vector a inicializar
 * @param capacidad del vector
 */
void vectorInicio(vectorDinamico *vector, int capacidadInicial){

    vector -> capacidad = capacidadInicial; //Inicializa la capacidad especificada
    vector -> totalElementos = 0; //Inicializa el total de elementos en 0 (aun no tiene elementos)

    //Reserva memoria para el arreglo de apuntadores
    vector -> elementos = malloc(sizeof(void *) * vector -> capacidad);

}

/*
 * Lee el fichero con enteros y los almacena en el vector
 * @param nombre de archivo
 * @param vector a llenar
 * @param capacidad del vector
 */
void leerFichero(char *nombreArchivo, vectorDinamico *vector, int capacidadVector){
    
    //Abrir el archivo en modo lectura
    FILE *archivo = fopen(nombreArchivo, "r");

    //Verifiación que se haya abierto el archivo
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return;
    }

    //Lee 'capacidadVector' veces
    for (int i = 0; i < capacidadVector; i++) {

        //Reserva memoria para un entero
        int *elemento = malloc(sizeof(int));

        //Intenta leer un entero del archivo y no lo puede leer (menos numeros de los esperados)
        if(fscanf(archivo, "%d", elemento) != 1){
            printf("La capacidad ingresada (%d) es mayor a la cantidad de elementos del archivo (%d)\n", capacidadVector, i);
            free(elemento);
            break;
        }

        //Almacena el apuntador al entero en el vector y actualiza el contador
        vector -> elementos[vector -> totalElementos++] = elemento;
    }

    //Cierra el archivo
    fclose(archivo);

}

/*
 * Calcula la suma de todos los elementos del vector
 * @param vector a sumar
 * @return la suma de todos los elementos del vector
 */
int sumarVector(vectorDinamico *vector){

    int suma = 0;

    //Recorre todos los elementos del vector
    for (int i = 0; i < vector -> totalElementos; i++) {

         // Convierte el apuntador generico a apuntador a entero y suma su valor
        int *elemento = (int *) vector -> elementos[i];
        suma += *elemento;
    }

    return suma;

}

/*
 * Libera la memoria reservada para el vector
 * @param vector a liberar
 */

void freeVector(vectorDinamico *vector) {

    if (vector->elementos) { // Verifica que el vector no sea NULL
        
        for (int i = 0; i < vector->totalElementos; i++)
            if (vector->elementos[i]) 
                free(vector->elementos[i]); // Libera cada entero del vector
            
        free(vector->elementos); // Libera el arreglo de punteros 

    }

}


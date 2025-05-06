# 🧠 Taller Fork() - Sistemas Operativos

**Autores:**  
Viviana Gómez, Gabriel Jaramillo, Roberth Méndez, Luz Adriana Salazar, Guden Silva  
**Fecha:** Abril 2025

## 📌 Descripción

Este proyecto consiste en un programa desarrollado en **lenguaje C** que realiza operaciones de suma entre dos arreglos de números enteros almacenados en archivos. Utiliza conceptos fundamentales de sistemas operativos como:

- Procesos (`fork`)
- Comunicación entre procesos (`pipe`)
- Gestión de memoria dinámica
- Sincronización de procesos (`wait`)

## 🎯 Objetivo

Leer dos archivos con enteros, almacenarlos dinámicamente en memoria y, mediante **cuatro procesos**, realizar cálculos parciales y totales de suma:

- **Gran hijo:** suma del primer arreglo.
- **Segundo hijo:** suma del segundo arreglo.
- **Primer hijo:** suma total (ambos arreglos).
- **Padre:** recibe los resultados y los imprime.

## ⚙️ Estructura del Proyecto

- `main.c`: Código fuente principal.
- `vectorDinamico`: Estructura personalizada para manejar vectores dinámicos de enteros.
- `leerFichero`: Función encargada de la lectura y validación de archivos de entrada.
- `pipes`: Dos pipes implementados para la comunicación entre procesos.

## 🛠️ Tecnologías Usadas

- Lenguaje C
- Librerías: `stdio.h`, `stdlib.h`, `unistd.h`, `sys/types.h`, `sys/wait.h`

## 🧪 Método de Prueba

1. **Lectura de archivos:**  
   Validación de lectura correcta de los elementos desde archivos con diferentes formatos y tamaños.

2. **Creación y comunicación de procesos:**  
   Verificación de que los procesos se crean correctamente y los datos se transmiten entre ellos sin errores.

3. **Liberación de recursos:**  
   Comprobación de que no haya fugas de memoria y cierre adecuado de procesos y descriptores de archivos.

## ✅ Resultados Esperados

Tras la ejecución del programa, se espera ver en la consola:

- La suma del arreglo A.
- La suma del arreglo B.
- La suma total (A + B).

Además, se asegura:

- Comunicación eficiente entre procesos.
- Gestión correcta de recursos del sistema.

## 🧳 Cómo Ejecutar

```bash
gcc main.c -o taller
./taller N1 archivoA.txt N2 archivoB.txt

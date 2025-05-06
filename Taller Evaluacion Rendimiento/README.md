## 🧳 Cómo Ejecutar

```bash
incluir chmod +x mmClasicaPosix mmClasicaFork mmClasicaOpenMP en caso de usar archivos pre-compilados

gcc mmClasicaPosix.c mmInterfazPosix.c -o mmClasicaPosix -pthread
gcc mmClasicaFork.c mmInterfazFork.c -o mmClasicaFork
gcc mmClasicaOpenMP.c mmInterfazOpenMP.c -o mmClasicaOpenMP -fopenmp
/usr/bin/perl ./lanza.pl

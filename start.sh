#!/bin/bash

# Compilar el archivo en C
gcc -o juego main.c tdas/list.c tdas/extra.c -Wno-unused-result -Wno-unused-variable -Wno-unused-function -lm



# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa. Ejecutando el juego..."
    ./main 
    

    # Ejecutar el archivo de Python
    
else
    echo "Error de compilación. No se pudo ejecutar el juego."
fi

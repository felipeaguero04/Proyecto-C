# Proyecto desarrollado en C
Proyecto de C, programación bajo plataformas abiertas

Descripción y uso del proyecto: Este proyecto desarrollará el juego de gato por medio de una interfaz gráfica con jugabilidad para dos jugadores.

Autores: Luis Felipe Aguero Peralta, Sebastian Vargas Quesada

Archivos: Se encuentran en la segunda rama, denominada "master".

# Instalación de bibliotecas

Se utilizará el kit de herramientas GTK de Glade para la interfaz gráfica, específicamente la versión 3.0, por lo que se deberá ejecutar el siguiente comando desde la terminal de linux para su respectiva instalación: 

$sudo apt install glade

Para compilar el programa desde la terminal de linux se pueden utilizar dos comandos:

gcc -o Gato main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

make total

La diferencia de estos comandos es que el comando make acepta el objetivo "total" como argumentos de línea de comando. Y este objetivo es especificado en el archivo adjutado denominado ‘Makefile’, que contiene la acción asociada correspondiente al objetivo "total" acción que es exactamente igual al primer comando definido.

Para ejecutar el programa desde la terminal de Linux se pueden utilizar estos dos comandos:

./Gato

make process

Finalmente para eliminar el archivo ejecutable se debe correr en la terminal de linux:

make remove

De igual forma aceptará el objetivo "remove" como argumentos de línea de comando. Y este objetivo es especificado en el archivo adjutado denominado ‘Makefile’, que contiene la acción asociada correspondiente al objetivo "remove" acción que utiliza el comando "rm" para eliminar el ejecutable Gato.


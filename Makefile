process:
		./Gato
remove:
		rm Gato
total:
		gcc -o Gato main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
#Final 

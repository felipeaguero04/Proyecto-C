process:
		./Gato
remove:
		rm Gato
total:
		gcc -o Gato tic_tac_toe.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
#Final

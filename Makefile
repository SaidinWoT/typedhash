cc=gcc

default:
	$(cc) -lncurses disp.c main.c hash.c -o ./hash

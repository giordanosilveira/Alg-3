trabalho: lista.o trabalho.o 
		gcc -g -Wall trabalho.o lista.o -lm -o trabalho

trabalho.o: lista.h trabalho.c
		gcc -Wall -g -c trabalho.c

lista.o: lista.c lista.h
		gcc -Wall -g -c lista.c
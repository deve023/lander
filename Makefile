CC := gcc
CFLAGS := -Wall -pedantic -std=c99 -c -g
LFLAGS := -lm -lSDL2

all: lander

main.o: main.c nave.h config.h vectores.h imprimir.h background.h terreno.h fisica.h imprimir.h matematica.h
	$(CC) $(CFLAGS) main.c

nave.o: nave.c nave.h config.h fisica.h vectores.h imprimir.h
	$(CC) $(CFLAGS) nave.c

terreno.o: terreno.c terreno.h config.h imprimir.h
	$(CC) $(CFLAGS) terreno.c

cielo.o: cielo.c cielo.h lista.h
	$(CC) $(CFLAGS) cielo.c

background.o: background.c background.h terreno.h cielo.h
	$(CC) $(CFLAGS) background.c

imprimir.o: imprimir.c imprimir.h diccionario.h caracteres.h vectores.h
	$(CC) $(CFLAGS) imprimir.c

caracteres.o: caracteres.c caracteres.h
	$(CC) $(CFLAGS) caracteres.c

diccionario.o: diccionario.c diccionario.h
	$(CC) $(CFLAGS) diccionario.c

vectores.o: vectores.c vectores.h
	$(CC) $(CFLAGS) vectores.c

fisica.o: fisica.c fisica.h
	$(CC) $(CFLAGS) fisica.c

lista.o: lista.c lista.h
	$(CC) $(CFLAGS) lista.c

lander: main.o nave.o terreno.o cielo.o imprimir.o caracteres.o diccionario.o vectores.o lista.o fisica.o matematica.o background.o
	$(CC) $^ -o lander $(LFLAGS)

clean:
	rm *.o

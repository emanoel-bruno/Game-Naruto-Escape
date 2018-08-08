SOURCES = main.c objeto.c personagem.c barra.c
HEADERS = objeto.h personagem.h barra.h
OBJECTS = main.o objeto.o personagem.o barra.o
LIBS    = -lglut -lGLU -lGL -lm -lSOIL
CFLAGS  = -O3 -Wall


all: tp1
 
tp1: $(OBJECTS)
	gcc -o tp1 $(OBJECTS) $(CFLAGS) $(LIBS)

objeto.o: objeto.c objeto.h
	gcc -o objeto.o -c objeto.c $(LIBS) -nostartfiles

personagem.o: personagem.c personagem.h
	gcc -o personagem.o -c personagem.c $(LIBS) -nostartfiles
 
barra.o: barra.c barra.h
	gcc -o barra.o -c barra.c $(LIBS) -nostartfiles

main.o: main.c $(HEADERS)
	gcc -o main.o -c main.c  $(LIBS)
clean:
	rm -rf *.o
clean-all: 
	rm -rf tp1 *.o


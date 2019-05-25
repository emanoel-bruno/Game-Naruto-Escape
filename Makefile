SOURCES = main.c objeto.c personagem.c barra.c
HEADERS = objeto.h personagem.h barra.h
OBJECTS = main.o objeto.o personagem.o barra.o
LIBS    = -lglut -lGLU -lGL -lm -lSOIL
CFLAGS  = -O3 -Wall


all: naruto-escape
 
naruto-escape: $(OBJECTS)
	gcc -o naruto-escape $(OBJECTS) $(CFLAGS) $(LIBS)
	rm -rf *.o

objeto.o: objeto.c objeto.h
	gcc -o objeto.o -c objeto.c $(LIBS) -nostartfiles

personagem.o: personagem.c personagem.h
	gcc -o personagem.o -c personagem.c $(LIBS) -nostartfiles
 
barra.o: barra.c barra.h
	gcc -o barra.o -c barra.c $(LIBS) -nostartfiles

main.o: main.c $(HEADERS)
	gcc -o main.o -c main.c  $(LIBS)

clean: 
	rm -rf naruto-escape *.o


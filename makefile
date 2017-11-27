CC = gcc
CFLAGS =
LDFLAGS = -lGL -lglut -lGLU -lm

FILES = texture.o sistema_solar.o

all: sistema_solar

sistema_solar: ${FILES}
	$(CC) $(CFLAGS) ${FILES} $(LDFLAGS) -o $@

sistema_solar.o: sistema_solar.c

texture.o: texture.h texture.c

.PHONY: clean realclean

clean:
	-rm -f *.o *~ 

realclean: clean
	-rm -f main

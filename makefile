CC = gcc
CFLAGS = -lGL -lglut -lGLU -lm

EXAMPLES = sistema_solar.c
	   

OUTPUTS = $(basename $(EXAMPLES))

.PHONY: clean

all: $(OUTPUTS)

%: %.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	-rm -f $(OUTPUTS) 

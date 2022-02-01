#openGL simple 2D render engine

P=../builds/test
SRC=main.c shader.c window.c block.c texture.c camera.c
OBJ=${SRC:.c=.o}
CFLAGS= -g -std=c17 -m64 -Wall -O3 `pkg-config --cflags glfw3 gl glew cglm` -I../include
LDFLAGS= `pkg-config --libs glfw3 gl glew cglm` -ldl -lm
CC=cc

all: main

.c.o:
	$(CC) -c $(CFLAGS) $<

$(OBJ): *.h

main: $(OBJ)
	$(CC) -o $(P) $(OBJ) $(LDFLAGS)

run: $(P)
	@$(P)

clean:
	@rm -f $(OBJ)

.PHONY: all clean run

# end

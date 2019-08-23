all: pong

pong: main.o paddle.o puck.o
	gcc -o pong main.o paddle.o puck.o -lSDL2 -lSDL2_ttf -lSDL2_gfx -lm

main.o: main.c pong.h puck.h paddle.h
	gcc -c main.c

paddle.o: paddle.c paddle.h pong.h
	gcc -c paddle.c

puck.o: puck.c puck.h pong.h
	gcc -c puck.c

clean:
	rm -f pong *.o

fullclean: clean
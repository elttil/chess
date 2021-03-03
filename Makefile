CC=g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CFLAGS=-Wall -Werror -pedantic

chess: *.cpp
	$(CC) -Wall $^ $(LIBS) $(CFLAGS) -o chess

run:
	./chess

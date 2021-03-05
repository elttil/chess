CC=g++
ODIR=obj
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS=-Wall -Werror -pedantic -g

SRC := $(wildcard *.cpp)
OBJ := king.o pawn.o game.o rook.o knight.o bishop.o piece.o queen.o main.o

all: chess

%.o: %.cpp
	$(CC) -c $< $(CPPFLAGS) -o $@

chess: $(OBJ)
	$(CC) $(LIBS) -o $@ $^

clean:
	rm -f chess *.o

run:
	./chess

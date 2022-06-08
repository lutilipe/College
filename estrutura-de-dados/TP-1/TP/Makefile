CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/poker.o $(OBJ)/player.o $(OBJ)/card.o $(OBJ)/game.o $(OBJ)/memlog.o $(OBJ)/hand.o
HDRS = $(INC)/player.h $(INC)/hand.h $(INC)/card.h $(INC)/game.h $(INC)/memlog.h $(INC)/stack.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/tp1

all: run

run: $(EXE) $(OUT)
	$(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/poker.o: $(HDRS) $(SRC)/poker.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker.o $(SRC)/poker.cpp

$(OBJ)/player.o: $(HDRS) $(SRC)/player.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/player.o $(SRC)/player.cpp 

$(OBJ)/hand.o: $(HDRS) $(SRC)/hand.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/hand.o $(SRC)/hand.cpp 

$(OBJ)/game.o: $(HDRS) $(SRC)/game.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/game.o $(SRC)/game.cpp 

$(OBJ)/card.o: $(HDRS) $(SRC)/card.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/card.o $(SRC)/card.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

mem: $(EXE)
	$(EXE) -l -p /tmp/poker_mem.out
	rm -rf /tmp/pokerest
	mkdir /tmp/pokerest
	$(ANALISAMEM) -i /tmp/poker_mem.out -p /tmp/pokerest/pokerest
	gnuplot /tmp/pokerest/*.gp

perf: $(EXE)
	$(EXE) -p /tmp/poker1m.out

gprof: $(EXE)
	$(EXE) -p /tmp/pokergprof.out 
	gprof $(EXE) gmon.out > /tmp/pokergprof.txt
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

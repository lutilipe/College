CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/poker.o $(OBJ)/player.o $(OBJ)/card.o $(OBJ)/deck.o $(OBJ)/game.o $(OBJ)/memlog.o
HDRS = $(INC)/player.h $(INC)/card.h $(INC)/deck.h $(INC)/game.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/poker

all:  mem perf gprof

mem: $(EXE) $(OUT)

perf: $(EXE) $(OUT)

gprof: $(EXE) $(OUT)

run: $(EXE) $(OUT)
	$(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/poker.o: $(HDRS) $(SRC)/poker.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker.o $(SRC)/poker.cpp

$(OBJ)/player.o: $(HDRS) $(SRC)/player.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/player.o $(SRC)/player.cpp 

$(OBJ)/game.o: $(HDRS) $(SRC)/game.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/game.o $(SRC)/game.cpp 

$(OBJ)/deck.o: $(HDRS) $(SRC)/deck.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/deck.o $(SRC)/deck.cpp 

$(OBJ)/card.o: $(HDRS) $(SRC)/card.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/card.o $(SRC)/card.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

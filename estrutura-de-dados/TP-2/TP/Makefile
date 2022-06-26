CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/analyzer.o $(OBJ)/word.o $(OBJ)/alphabeticOrder.o $(OBJ)/utils.o
HDRS = $(INC)/memlog.h $(INC)/utils.h $(INC)/msgassert.h $(INC)/word.h $(INC)/wordVector.h $(INC)/alphabeticOrder.h
CFLAGS = -pg -Wall -c -I$(INC) -O3
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/tp2

all: run

run: $(EXE) $(OUT)
	$(EXE) -I entrada.txt -o saida.txt -m 5 -S 54

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/analyzer.o: $(HDRS) $(SRC)/analyzer.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/analyzer.o $(SRC)/analyzer.cpp 

$(OBJ)/alphabeticOrder.o: $(HDRS) $(SRC)/alphabeticOrder.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/alphabeticOrder.o $(SRC)/alphabeticOrder.cpp

$(OBJ)/word.o: $(HDRS) $(SRC)/word.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/word.o $(SRC)/word.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

$(OBJ)/utils.o: $(HDRS) $(SRC)/utils.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/utils.o $(SRC)/utils.cpp

mem: $(EXE)

perf: $(EXE)

gprof: $(EXE)

clean:
	rm -f $(EXE) $(OBJS) gmon.out

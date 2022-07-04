CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/analyzer.o $(OBJ)/word.o $(OBJ)/alphabeticOrder.o $(OBJ)/utils.o $(OBJ)/memlog.o $(OBJ)/letter.o
HDRS = $(INC)/memlog.h $(INC)/utils.h $(INC)/msgassert.h $(INC)/word.h $(INC)/wordVector.h $(INC)/alphabeticOrder.h $(INC)/letter.h
CFLAGS = -pg -Wall -c -I$(INC) -O3
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/tp2

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/analyzer.o: $(HDRS) $(SRC)/analyzer.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/analyzer.o $(SRC)/analyzer.cpp 

$(OBJ)/alphabeticOrder.o: $(HDRS) $(SRC)/alphabeticOrder.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/alphabeticOrder.o $(SRC)/alphabeticOrder.cpp

$(OBJ)/letter.o: $(HDRS) $(SRC)/letter.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/letter.o $(SRC)/letter.cpp

$(OBJ)/word.o: $(HDRS) $(SRC)/word.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/word.o $(SRC)/word.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

$(OBJ)/utils.o: $(HDRS) $(SRC)/utils.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/utils.o $(SRC)/utils.cpp

mem: $(EXE)
	$(EXE) -l -p output.txt -I entrada.txt -o saida.txt -m 5 -S 3
	rm -rf /tmp/analyzerest
	mkdir /tmp/analyzerest
	$(ANALISAMEM) -i output.txt -p /tmp/analyzerest/analyzerest
	gnuplot /tmp/analyzerest/*.gp

perf: $(EXE)
	$(EXE) -I entrada.txt -o saida.txt -m 3 -S 40000 -p output.txt

gprof: $(EXE)
	$(EXE) -I entrada.txt -o saida.txt -m 100 -S 3
	gprof $(EXE) gmon.out > /tmp/analyzerest.txt

clean:
	rm -f $(EXE) $(OBJS) gmon.out

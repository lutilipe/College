CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/email.o $(OBJ)/email-server.o $(OBJ)/email-box.o $(OBJ)/memlog.o
HDRS = $(INC)/email.h $(INC)/email-server.h $(INC)/email-box.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC) -O3
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/tp3

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -pg -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp 

$(OBJ)/email.o: $(HDRS) $(SRC)/email.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/email.o $(SRC)/email.cpp

$(OBJ)/email-box.o: $(HDRS) $(SRC)/email-box.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/email-box.o $(SRC)/email-box.cpp

$(OBJ)/email-server.o: $(HDRS) $(SRC)/email-server.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/email-server.o $(SRC)/email-server.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp

mem: $(EXE)
	$(EXE) -l -p /tmp/poker_mem.out
	rm -rf /tmp/pokerest
	mkdir /tmp/pokerest
	$(ANALISAMEM) -i /tmp/poker_mem.out -p /tmp/pokerest/pokerest
	gnuplot /tmp/pokerest/*.gp

perf: $(EXE)
	$(EXE) -p /tmp/poker10m.out

gprof: $(EXE)
	$(EXE) -p /tmp/pokergprof.out 
	gprof $(EXE) gmon.out > /tmp/pokergprof.txt
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

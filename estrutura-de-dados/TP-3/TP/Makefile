CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/email.o $(OBJ)/email-server.o $(OBJ)/email-box.o $(OBJ)/memlog.o
HDRS = $(INC)/email.h $(INC)/email-server.h $(INC)/email-box.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC) -O3
ANALISAMEM = ../../analisamem/bin/analisamem

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
	$(EXE) -l -p ./email_mem.out -i entrada.txt -o saida.txt
	rm -rf ./emailest
	mkdir ./emailest
	$(ANALISAMEM) -i ./email_mem.out -p ./emailest/emailest
	gnuplot ./emailest/*.gp

perf: $(EXE)
	$(EXE) -p ./email2000.out -i entrada.txt -o saida.txt

gprof: $(EXE)
	$(EXE) -i entrada.txt -o saida.txt
	gprof $(EXE) gmon.out > ./emailgprof.txt
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

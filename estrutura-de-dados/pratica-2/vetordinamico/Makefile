#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa vetop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2022-04-01 - arquivo criado
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/vetop.o $(OBJ)/vet.o $(OBJ)/memlog.o
HDRS = $(INC)/vet.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/vetop

all:  mem perf gprof

mem: $(EXE)
	rm -rf ./out
	mkdir out
	$(EXE) -d 20 -s -p ./out/somalog.out -l 
	rm -rf ./out/somadin
	mkdir ./out/somadin
	$(ANALISAMEM) -i ./out/somalog.out -p ./out/somadin/somadin
	$(EXE) -d 20 -i -p ./out/internolog.out -l 
	rm -rf ./out/internodin
	mkdir ./out/internodin
	$(ANALISAMEM) -i ./out/internolog.out -p ./out/internodin/internodin
	$(EXE) -d 20 -n -p ./out/normalog.out -l 
	rm -rf ./out/normadin
	mkdir ./out/normadin
	$(ANALISAMEM) -i ./out/normalog.out -p ./out/normadin/normadin

perf: $(EXE)
	$(EXE) -d 1000000 -s -p ./out/soma1M.out
	$(EXE) -d 1000000 -i -p ./out/interno1M.out
	$(EXE) -d 1000000 -n -p ./out/norma1M.out
	$(EXE) -d 2000000 -s -p ./out/soma2M.out
	$(EXE) -d 2000000 -i -p ./out/interno2M.out
	$(EXE) -d 2000000 -n -p ./out/norma2M.out
	$(EXE) -d 3000000 -s -p ./out/soma3M.out
	$(EXE) -d 3000000 -i -p ./out/interno3M.out
	$(EXE) -d 3000000 -n -p ./out/norma3M.out
	$(EXE) -d 4000000 -s -p ./out/soma4M.out
	$(EXE) -d 4000000 -i -p ./out/interno4M.out
	$(EXE) -d 4000000 -n -p ./out/norma4M.out
	$(EXE) -d 5000000 -s -p ./out/soma5M.out
	$(EXE) -d 5000000 -i -p ./out/interno5M.out
	$(EXE) -d 5000000 -n -p ./out/norma5M.out

gprof: $(BIN)/vetop
	$(EXE) -d 5000000 -s -p ./out/soma5Mgprof.out 
	gprof $(EXE) gmon.out > ./out/soma5Mgprof.txt
	$(EXE) -d 5000000 -i -p ./out/interno5Mgprof.out 
	gprof $(EXE) gmon.out > ./out/interno5Mgprof.txt
	$(EXE) -d 5000000 -n -p ./out/norma5Mgprof.out 
	gprof $(EXE) gmon.out > ./out/norma5Mgprof.txt
	

$(BIN)/vetop: $(OBJS)
	$(CC) -pg -o $(BIN)/vetop $(OBJS) $(LIBS)

$(OBJ)/vetop.o: $(HDRS) $(SRC)/vetop.c
	$(CC) $(CFLAGS) -o $(OBJ)/vetop.o $(SRC)/vetop.c 

$(OBJ)/vet.o: $(HDRS) $(SRC)/vet.c
	$(CC) $(CFLAGS) -o $(OBJ)/vet.o $(SRC)/vet.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

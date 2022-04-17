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
	$(EXE) -d 20 -s -p /tmp/somalog.out -l 
	rm -rf /tmp/somadin
	mkdir /tmp/somadin
	$(ANALISAMEM) -i /tmp/somalog.out -p /tmp/somadin/somadin
	$(EXE) -d 20 -i -p /tmp/internolog.out -l 
	rm -rf /tmp/internodin
	mkdir /tmp/internodin
	$(ANALISAMEM) -i /tmp/internolog.out -p /tmp/internodin/internodin
	$(EXE) -d 20 -n -p /tmp/normalog.out -l 
	rm -rf /tmp/normadin
	mkdir /tmp/normadin
	$(ANALISAMEM) -i /tmp/normalog.out -p /tmp/normadin/normadin

perf: $(EXE)
	$(EXE) -d 1000000 -s -p /tmp/soma1M.out
	$(EXE) -d 1000000 -i -p /tmp/interno1M.out
	$(EXE) -d 1000000 -n -p /tmp/norma1M.out
	$(EXE) -d 2000000 -s -p /tmp/soma2M.out
	$(EXE) -d 2000000 -i -p /tmp/interno2M.out
	$(EXE) -d 2000000 -n -p /tmp/norma2M.out
	$(EXE) -d 3000000 -s -p /tmp/soma3M.out
	$(EXE) -d 3000000 -i -p /tmp/interno3M.out
	$(EXE) -d 3000000 -n -p /tmp/norma3M.out
	$(EXE) -d 4000000 -s -p /tmp/soma4M.out
	$(EXE) -d 4000000 -i -p /tmp/interno4M.out
	$(EXE) -d 4000000 -n -p /tmp/norma4M.out
	$(EXE) -d 5000000 -s -p /tmp/soma5M.out
	$(EXE) -d 5000000 -i -p /tmp/interno5M.out
	$(EXE) -d 5000000 -n -p /tmp/norma5M.out

gprof: $(BIN)/vetop
	$(EXE) -d 5000000 -s -p /tmp/soma5Mgprof.out 
	gprof $(EXE) gmon.out > /tmp/soma5Mgprof.txt
	$(EXE) -d 5000000 -i -p /tmp/interno5Mgprof.out 
	gprof $(EXE) gmon.out > /tmp/interno5Mgprof.txt
	$(EXE) -d 5000000 -n -p /tmp/norma5Mgprof.out 
	gprof $(EXE) gmon.out > /tmp/norma5Mgprof.txt
	

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

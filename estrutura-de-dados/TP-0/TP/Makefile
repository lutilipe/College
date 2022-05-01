#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
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
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)
OUT = ../out
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/matop

all:  mem perf gprof

mem: $(EXE) $(OUT)
	if test -d $(OUT)/mem; then rm -rf $(OUT)/mem; fi
	mkdir $(OUT)/mem

	$(EXE) -s -p $(OUT)/mem/somalog.out -l -x 4 -y 5
	if test -d $(OUT)/mem/soma; then rm -rf $(OUT)/mem/soma; fi
	mkdir ../out/mem/soma
	$(ANALISAMEM) -i $(OUT)/mem/somalog.out -p $(OUT)/mem/soma/
	gnuplot ../out/mem/soma/*.gp

	$(EXE) -m -p $(OUT)/mem/multlog.out -l -x 5 -y 5
	if test -d $(OUT)/mem/mul; then rm -rf $(OUT)/mem/mul; fi
	mkdir ../out/mem/mul
	$(ANALISAMEM) -i $(OUT)/mem/multlog.out -p $(OUT)/mem/mul/
	gnuplot ../out/mem/mul/*.gp

	$(EXE) -t -p $(OUT)/mem/transplog.out -l -x 5 -y 4
	if test -d $(OUT)/mem/transp; then rm -rf $(OUT)/mem/transp; fi
	mkdir ../out/mem/transp
	$(ANALISAMEM) -i $(OUT)/mem/transplog.out -p $(OUT)/mem/transp/
	gnuplot ../out/mem/transp/*.gp

perf: $(EXE) $(OUT)
	if test -d $(OUT)/perf; then rm -rf $(OUT)/perf; fi
	mkdir $(OUT)/perf
	$(EXE) -s -p $(OUT)/perf/soma100.out  -x 100 -y 100
	$(EXE) -m -p $(OUT)/perf/mult100.out  -x 100 -y 100
	$(EXE) -t -p $(OUT)/perf/transp100.out  -x 100 -y 100
	$(EXE) -s -p $(OUT)/perf/soma200.out  -x 200 -y 200
	$(EXE) -m -p $(OUT)/perf/mult200.out  -x 200 -y 200
	$(EXE) -t -p $(OUT)/perf/transp200.out  -x 200 -y 200
	$(EXE) -s -p $(OUT)/perf/soma300.out  -x 300 -y 300
	$(EXE) -m -p $(OUT)/perf/mult300.out  -x 300 -y 300
	$(EXE) -t -p $(OUT)/perf/transp300.out  -x 300 -y 300
	$(EXE) -s -p $(OUT)/perf/soma400.out  -x 400 -y 400
	$(EXE) -m -p $(OUT)/perf/mult400.out  -x 400 -y 400
	$(EXE) -t -p $(OUT)/perf/transp400.out  -x 400 -y 400
	$(EXE) -s -p $(OUT)/perf/soma500.out  -x 500 -y 500
	$(EXE) -m -p $(OUT)/perf/mult500.out  -x 500 -y 500
	$(EXE) -t -p $(OUT)/perf/transp500.out  -x 500 -y 500
	$(EXE) -m -p $(OUT)/perf/mult100log.out -l -x 100 -y 100

gprof: $(EXE) $(OUT)
	if test -d $(OUT)/gprof; then rm -rf $(OUT)/gprof; fi
	mkdir $(OUT)/gprof
	$(EXE) -s -p $(OUT)/gprof/soma500gprof.out  -x 500 -y 500
	gprof $(EXE) gmon.out > $(OUT)/gprof/soma500gprof.txt
	$(EXE) -m -p $(OUT)/gprof/mult500gprof.out  -x 500 -y 500
	gprof $(EXE) gmon.out > $(OUT)/gprof/mult500gprof.txt
	$(EXE) -t -p $(OUT)/gprof/transp500gprof.out  -x 500 -y 500
	gprof $(EXE) gmon.out > $(OUT)/gprof/transp500gprof.txt

$(OUT):
	mkdir -p $(OUT)

$(BIN)/matop: $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out

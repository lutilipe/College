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
IN = ../in
ANALISAMEM = ../analisamem/bin/analisamem

EXE = $(BIN)/matop

all:  mem perf gprof

mem: $(EXE) $(OUT)
	if test -d $(OUT)/mem; then rm -rf $(OUT)/mem; fi
	mkdir $(OUT)/mem

	if test -d $(OUT)/mem/sum; then rm -rf $(OUT)/mem/sum; fi
	mkdir $(OUT)/mem/sum
	$(EXE) -s -p $(OUT)/mem/somalog.out -l -1 $(IN)/sum/m1.txt -2 $(IN)/sum/m2.txt -o $(OUT)/mem/sum/res.out
	$(ANALISAMEM) -i $(OUT)/mem/somalog.out -p $(OUT)/mem/sum/
	gnuplot $(OUT)/mem/sum/*.gp

	if test -d $(OUT)/mem/mult; then rm -rf $(OUT)/mem/mult; fi
	mkdir $(OUT)/mem/mult
	$(EXE) -m -p $(OUT)/mem/multlog.out -l -1 $(IN)/mult/m1.txt -2 $(IN)/mult/m2.txt -o $(OUT)/mem/mult/res.out
	$(ANALISAMEM) -i $(OUT)/mem/multlog.out -p $(OUT)/mem/mult/
	gnuplot $(OUT)/mem/mult/*.gp

	if test -d $(OUT)/mem/transp; then rm -rf $(OUT)/mem/transp; fi
	mkdir $(OUT)/mem/transp
	$(EXE) -t -p $(OUT)/mem/transplog.out -l -1 $(IN)/transp/m1.txt -o $(OUT)/mem/transp/res.out
	$(ANALISAMEM) -i $(OUT)/mem/transplog.out -p $(OUT)/mem/transp/
	gnuplot $(OUT)/mem/transp/*.gp

perf: $(EXE) $(OUT)
	if test -d $(OUT)/perf; then rm -rf $(OUT)/perf; fi
	mkdir $(OUT)/perf

	if test -d $(OUT)/perf/sum; then rm -rf $(OUT)/perf/sum; fi
	mkdir $(OUT)/perf/sum
	$(EXE) -s -p $(OUT)/perf/sum/soma100.out -1 $(IN)/sum/m1.txt -2 $(IN)/sum/m2.txt -o $(OUT)/perf/sum/res.out
	$(EXE) -s -p $(OUT)/perf/sum/soma200.out -1 $(IN)/sum/m1.txt -2 $(IN)/sum/m2.txt -o $(OUT)/perf/sum/res.out
	$(EXE) -s -p $(OUT)/perf/sum/soma300.out -1 $(IN)/sum/m1.txt -2 $(IN)/sum/m2.txt -o $(OUT)/perf/sum/res.out
	$(EXE) -s -p $(OUT)/perf/sum/soma400.out -1 $(IN)/sum/m1.txt -2 $(IN)/sum/m2.txt -o $(OUT)/perf/sum/res.out
	$(EXE) -s -p $(OUT)/perf/sum/soma500.out -1 $(IN)/sum/m1.txt -2 $(IN)/sum/m2.txt -o $(OUT)/perf/sum/res.out

	if test -d $(OUT)/perf/mult; then rm -rf $(OUT)/perf/mult; fi
	mkdir $(OUT)/perf/mult
	$(EXE) -m -p $(OUT)/perf/mult/mult100.out -1 $(IN)/mult/m1.txt -2 $(IN)/mult/m2.txt -o $(OUT)/perf/mult/res.out
	$(EXE) -m -p $(OUT)/perf/mult/mult200.out -1 $(IN)/mult/m1.txt -2 $(IN)/mult/m2.txt -o $(OUT)/perf/mult/res.out
	$(EXE) -m -p $(OUT)/perf/mult/mult300.out -1 $(IN)/mult/m1.txt -2 $(IN)/mult/m2.txt -o $(OUT)/perf/mult/res.out
	$(EXE) -m -p $(OUT)/perf/mult/mult400.out -1 $(IN)/mult/m1.txt -2 $(IN)/mult/m2.txt -o $(OUT)/perf/mult/res.out
	$(EXE) -m -p $(OUT)/perf/mult/mult500.out -1 $(IN)/mult/m1.txt -2 $(IN)/mult/m2.txt -o $(OUT)/perf/mult/res.out

	if test -d $(OUT)/perf/transp; then rm -rf $(OUT)/perf/transp; fi
	mkdir $(OUT)/perf/transp
	$(EXE) -t -p $(OUT)/perf/transp/transp100.out -1 $(IN)/transp/m1.txt -o $(OUT)/perf/transp/res.out 
	$(EXE) -t -p $(OUT)/perf/transp/transp200.out -1 $(IN)/transp/m1.txt -o $(OUT)/perf/transp/res.out
	$(EXE) -t -p $(OUT)/perf/transp/transp300.out -1 $(IN)/transp/m1.txt -o $(OUT)/perf/transp/res.out
	$(EXE) -t -p $(OUT)/perf/transp/transp400.out -1 $(IN)/transp/m1.txt -o $(OUT)/perf/transp/res.out
	$(EXE) -t -p $(OUT)/perf/transp/transp500.out -1 $(IN)/transp/m1.txt -o $(OUT)/perf/transp/res.out

gprof: $(EXE) $(OUT)
	if test -d $(OUT)/gprof; then rm -rf $(OUT)/gprof; fi
	mkdir $(OUT)/gprof

	if test -d $(OUT)/gprof/sum; then rm -rf $(OUT)/gprof/sum; fi
	mkdir $(OUT)/gprof/sum
	$(EXE) -s -p $(OUT)/gprof/sum/soma500gprof.out -l -1 $(IN)/sum/m1.txt -2 $(IN)/sum/m2.txt -o $(OUT)/gprof/sum/res.out
	gprof $(EXE) gmon.out > $(OUT)/gprof/sum/soma500gprof.txt

	if test -d $(OUT)/gprof/mult; then rm -rf $(OUT)/gprof/mult; fi
	mkdir $(OUT)/gprof/mult
	$(EXE) -m -p $(OUT)/gprof/mult/mult500gprof.out -l -1 $(IN)/mult/m1.txt -2 $(IN)/mult/m2.txt -o $(OUT)/gprof/mult/res.out
	gprof $(EXE) gmon.out > $(OUT)/gprof/mult/mult500gprof.txt

	if test -d $(OUT)/gprof/transp; then rm -rf $(OUT)/gprof/transp; fi
	mkdir $(OUT)/gprof/transp
	$(EXE) -t -p $(OUT)/gprof/transp/transp500gprof.out -l -1 $(IN)/transp/m1.txt -o $(OUT)/gprof/transp/res.out
	gprof $(EXE) gmon.out > $(OUT)/gprof/transp/transp500gprof.txt

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

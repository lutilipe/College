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
	$(EXE) -s -p $(OUT)/mem/somalog.out -l -1 $(IN)/sum/5x5.txt -2 $(IN)/sum/5x5.txt -o $(OUT)/mem/sum/res-5x5.out
	$(ANALISAMEM) -i $(OUT)/mem/somalog.out -p $(OUT)/mem/sum/
	gnuplot $(OUT)/mem/sum/*.gp

	if test -d $(OUT)/mem/mult; then rm -rf $(OUT)/mem/mult; fi
	mkdir $(OUT)/mem/mult
	$(EXE) -m -p $(OUT)/mem/multlog.out -l -1 $(IN)/mult/5x5.txt -2 $(IN)/mult/5x5.txt -o $(OUT)/mem/mult/res-5x5.out
	$(ANALISAMEM) -i $(OUT)/mem/multlog.out -p $(OUT)/mem/mult/
	gnuplot $(OUT)/mem/mult/*.gp

	if test -d $(OUT)/mem/transp; then rm -rf $(OUT)/mem/transp; fi
	mkdir $(OUT)/mem/transp
	$(EXE) -t -p $(OUT)/mem/transplog.out -l -1 $(IN)/transp/5x5.txt -o $(OUT)/mem/transp/res-5x5.out
	$(ANALISAMEM) -i $(OUT)/mem/transplog.out -p $(OUT)/mem/transp/
	gnuplot $(OUT)/mem/transp/*.gp

perf: $(EXE) $(OUT)
	if test -d $(OUT)/perf; then rm -rf $(OUT)/perf; fi
	mkdir $(OUT)/perf

	if test -d $(OUT)/perf/sum; then rm -rf $(OUT)/perf/sum; fi
	mkdir $(OUT)/perf/sum
	$(EXE) -s -p $(OUT)/perf/sum/soma100.out -1 $(IN)/sum/100x100.txt -2 $(IN)/sum/100x100.txt -o $(OUT)/perf/sum/res-100x100.out
	$(EXE) -s -p $(OUT)/perf/sum/soma200.out -1 $(IN)/sum/200x200.txt -2 $(IN)/sum/200x200.txt -o $(OUT)/perf/sum/res-200x200.out
	$(EXE) -s -p $(OUT)/perf/sum/soma300.out -1 $(IN)/sum/300x300.txt -2 $(IN)/sum/300x300.txt -o $(OUT)/perf/sum/res-300x300.out
	$(EXE) -s -p $(OUT)/perf/sum/soma400.out -1 $(IN)/sum/400x400.txt -2 $(IN)/sum/400x400.txt -o $(OUT)/perf/sum/res-400x400.out
	$(EXE) -s -p $(OUT)/perf/sum/soma500.out -1 $(IN)/sum/500x500.txt -2 $(IN)/sum/500x500.txt -o $(OUT)/perf/sum/res-500x500.out

	if test -d $(OUT)/perf/mult; then rm -rf $(OUT)/perf/mult; fi
	mkdir $(OUT)/perf/mult
	$(EXE) -m -p $(OUT)/perf/mult/mult100.out -1 $(IN)/mult/100x100.txt -2 $(IN)/mult/100x100.txt -o $(OUT)/perf/mult/res-100x100.out
	$(EXE) -m -p $(OUT)/perf/mult/mult200.out -1 $(IN)/mult/200x200.txt -2 $(IN)/mult/200x200.txt -o $(OUT)/perf/mult/res-200x200.out
	$(EXE) -m -p $(OUT)/perf/mult/mult300.out -1 $(IN)/mult/300x300.txt -2 $(IN)/mult/300x300.txt -o $(OUT)/perf/mult/res-300x300.out
	$(EXE) -m -p $(OUT)/perf/mult/mult400.out -1 $(IN)/mult/400x400.txt -2 $(IN)/mult/400x400.txt -o $(OUT)/perf/mult/res-400x400.out
	$(EXE) -m -p $(OUT)/perf/mult/mult500.out -1 $(IN)/mult/500x500.txt -2 $(IN)/mult/500x500.txt -o $(OUT)/perf/mult/res-500x500.out

	if test -d $(OUT)/perf/transp; then rm -rf $(OUT)/perf/transp; fi
	mkdir $(OUT)/perf/transp
	$(EXE) -t -p $(OUT)/perf/transp/transp100.out -1 $(IN)/transp/100x100.txt -o $(OUT)/perf/transp/res-100x100.out 
	$(EXE) -t -p $(OUT)/perf/transp/transp200.out -1 $(IN)/transp/200x200.txt -o $(OUT)/perf/transp/res-200x200.out
	$(EXE) -t -p $(OUT)/perf/transp/transp300.out -1 $(IN)/transp/300x300.txt -o $(OUT)/perf/transp/res-300x300.out
	$(EXE) -t -p $(OUT)/perf/transp/transp400.out -1 $(IN)/transp/400x400.txt -o $(OUT)/perf/transp/res-400x400.out
	$(EXE) -t -p $(OUT)/perf/transp/transp500.out -1 $(IN)/transp/500x500.txt -o $(OUT)/perf/transp/res-500x500.out

gprof: $(EXE) $(OUT)
	if test -d $(OUT)/gprof; then rm -rf $(OUT)/gprof; fi
	mkdir $(OUT)/gprof

	if test -d $(OUT)/gprof/sum; then rm -rf $(OUT)/gprof/sum; fi
	mkdir $(OUT)/gprof/sum
	$(EXE) -s -p $(OUT)/gprof/sum/soma1000gprof.out -1 $(IN)/sum/1000x1000.txt -2 $(IN)/sum/1000x1000.txt -o $(OUT)/gprof/sum/res-1000x1000.out
	gprof $(EXE) gmon.out > $(OUT)/gprof/sum/soma1000gprof.txt

	if test -d $(OUT)/gprof/mult; then rm -rf $(OUT)/gprof/mult; fi
	mkdir $(OUT)/gprof/mult
	$(EXE) -m -p $(OUT)/gprof/mult/mult1000gprof.out -1 $(IN)/mult/1000x1000.txt -2 $(IN)/mult/1000x1000.txt -o $(OUT)/gprof/mult/res-1000x1000.out
	gprof $(EXE) gmon.out > $(OUT)/gprof/mult/mult1000gprof.txt

	if test -d $(OUT)/gprof/transp; then rm -rf $(OUT)/gprof/transp; fi
	mkdir $(OUT)/gprof/transp
	$(EXE) -t -p $(OUT)/gprof/transp/transp1000gprof.out -1 $(IN)/transp/1000x1000.txt -o $(OUT)/gprof/transp/res-1000x1000.out
	gprof $(EXE) gmon.out > $(OUT)/gprof/transp/transp1000gprof.txt

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

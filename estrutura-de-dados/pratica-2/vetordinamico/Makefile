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
	if test -d ../out/mem; then rm -rf ../out/mem; fi
	mkdir ../out/mem
	$(EXE) -d 20 -s -p ../out/mem/somalog.out -l 
	rm -rf ../out/mem/somadin
	mkdir ../out/mem/somadin
	$(ANALISAMEM) -i ../out/mem/somalog.out -p ../out/mem/somadin/
	gnuplot ../out/mem/somadin/*.gp
	$(EXE) -d 20 -i -p ../out/mem/internolog.out -l 
	rm -rf ../out/mem/internodin
	mkdir ../out/mem/internodin
	$(ANALISAMEM) -i ../out/mem/internolog.out -p ../out/mem/internodin/
	gnuplot ../out/mem/internodin/*.gp
	$(EXE) -d 20 -n -p ../out/mem/normalog.out -l 
	rm -rf ../out/mem/normadin
	mkdir ../out/mem/normadin
	$(ANALISAMEM) -i ../out/mem/normalog.out -p ../out/mem/normadin/
	gnuplot ../out/mem/normadin/*.gp

perf: $(EXE)
	if test -d ../out/perf; then rm -rf ../out/perf; fi
	mkdir ../out/perf
	$(EXE) -d 1000000 -s -p ../out/perf/soma1M.out
	$(EXE) -d 1000000 -i -p ../out/perf/interno1M.out
	$(EXE) -d 1000000 -n -p ../out/perf/norma1M.out
	$(EXE) -d 2000000 -s -p ../out/perf/soma2M.out
	$(EXE) -d 2000000 -i -p ../out/perf/interno2M.out
	$(EXE) -d 2000000 -n -p ../out/perf/norma2M.out
	$(EXE) -d 3000000 -s -p ../out/perf/soma3M.out
	$(EXE) -d 3000000 -i -p ../out/perf/interno3M.out
	$(EXE) -d 3000000 -n -p ../out/perf/norma3M.out
	$(EXE) -d 4000000 -s -p ../out/perf/soma4M.out
	$(EXE) -d 4000000 -i -p ../out/perf/interno4M.out
	$(EXE) -d 4000000 -n -p ../out/perf/norma4M.out
	$(EXE) -d 5000000 -s -p ../out/perf/soma5M.out
	$(EXE) -d 5000000 -i -p ../out/perf/interno5M.out
	$(EXE) -d 5000000 -n -p ../out/perf/norma5M.out

gprof: $(BIN)/vetop
	if test -d ../out/gprof; then rm -rf ../out/gprof; fi
	mkdir ../out/gprof
	$(EXE) -d 5000000 -s -p ../out/gprof/soma5Mgprof.out 
	gprof $(EXE) gmon.out > ../out/gprof/soma5Mgprof.txt
	$(EXE) -d 5000000 -i -p ../out/gprof/interno5Mgprof.out 
	gprof $(EXE) gmon.out > ../out/gprof/interno5Mgprof.txt
	$(EXE) -d 5000000 -n -p ../out/gprof/norma5Mgprof.out 
	gprof $(EXE) gmon.out > ../out/gprof/norma5Mgprof.txt
	

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

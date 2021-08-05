CC			= g++
CFLAGS		= -std=c++11 -Wall
TARGET 		= vpl_execution

INCLUDE 	= ./include
BUILD 		= ./build
SRC 		= ./src
ENTITY 		= ${SRC}/entidades
EXECUTABLE 	= main

${TARGET}: ${BUILD}/main.o ${BUILD}/Cilindro.o ${BUILD}/Circulo.o ${BUILD}/Ponto.o
	${CC} ${CFLAGS} -o ${TARGET} ${BUILD}/*.o

${BUILD}/Ponto.o: ${INCLUDE}/Ponto.hpp ${ENTITY}/Ponto.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${ENTITY}/Ponto.cpp -o ${BUILD}/Ponto.o

${BUILD}/Cilindro.o: ${INCLUDE}/Cilindro.hpp ${ENTITY}/Cilindro.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${ENTITY}/Cilindro.cpp -o ${BUILD}/Cilindro.o

${BUILD}/Circulo.o: ${INCLUDE}/Circulo.hpp ${ENTITY}/Circulo.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${ENTITY}/Circulo.cpp -o ${BUILD}/Circulo.o

${BUILD}/main.o: ${INCLUDE}/Ponto.hpp ${INCLUDE}/Cilindro.hpp ${INCLUDE}/Circulo.hpp ${SRC}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE} -c ${SRC}/main.cpp -o ${BUILD}/main.o

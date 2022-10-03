##############################################
# problema de classificação
rm(list=ls())
source('treinaperceptron.R')
source('yperceptron.R')
library('plot3D')
library("mlbench")

calc_acc <- function(x,w){
  total <- 0
  for (i in 1:nrow(x)) {
    if (x[i] == w[i]) {
      total <- total + 1
    }
  }
  return (total/nrow(x))
}

#pega os dados da package mlbench
data("BreastCancer")
data2 <- BreastCancer
#Realiza o tratamento dos dados para remoção de NA
data2 <- data2[complete.cases(data2),]

y<-matrix(0,nrow=nrow(data2))

for (i in 1:nrow(data2)) {
  if (data2[i,11] == 'benign') {
    y[i] = 1
  } else {
    y[i]= -1
  }
}

data2<-data2[,-11]
data2<-data2[,-1]
data2 <- cbind(data2, y)

n_folds<-10

folds <- cut(seq(1,nrow(data2)),breaks=n_folds,labels=FALSE)

eta<-0.01
tol<-0.001
mxepoc<-200

y<-matrix(0,nrow=n_folds)

for(i in 1:n_folds){

  testIndexes <- which(folds==i,arr.ind=TRUE)
  testData <- data2[testIndexes, ]
  trainData <- data2[-testIndexes, ]
  
  retlist<-treinaperceptron(data.matrix(trainData[,c(1:9)]),data.matrix(trainData[,10]),eta,tol,mxepoc,1)
  
  wt<-retlist[[1]]
  yhati<-yperceptron(data.matrix(testData[,c(1:9)]), wt, 1)
  y[i] = 1-(t(data.matrix(testData[,10] - yhati) %*% t(data.matrix(testData[,10] - yhati))))
}

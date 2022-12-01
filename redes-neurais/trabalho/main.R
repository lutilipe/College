rm(list = ls())
source("treinaMLP.R")
source("YMLP.R")
library(r2r)

trainDataSource <- read.csv("./dados/treino.csv", header = T)
testDataSource <- read.csv("./dados/validacao.csv", header = T)

tol<-0.1
eta<-0.01
maxepocas<-50

n_folds = 10

{
  ## Mapping labels
  labelMap <- hashmap()
  
  labelMap[["teens"]] = 1
  labelMap[["twenties"]] = 2
  labelMap[["thirties"]] = 3
  labelMap[["fourties"]] = 4
  labelMap[["fifties"]] = 5
  
  numberMap <- hashmap()
  
  numberMap[["1"]] = "teens"
  numberMap[["2"]] = "twenties"
  numberMap[["3"]] = "thirties"
  numberMap[["4"]] = "fourties"
  numberMap[["5"]] = "fifties"
}

numberMap[["2"]]

## Aux functions
decodeClassLabels2 <- function(labels, bitSize = 3) {
  bitLabel <- matrix(0, nrow=length(labels), ncol=bitSize)
  for (i in 1:length(labels)) {

    num <- labelMap[[toString(labels[i])]]

    m <- sapply(num,function(x){ as.integer(intToBits(x))})[1:bitSize]
    bitLabel[i,] <- bitLabel[i,] + t(as.matrix(m))
  }
  return(bitLabel)
}

bitToInt <- function(bit) {
  total <- 0
  currExp <- 0
  for (i in 1:ncol(bit)) {
    num <- (2^currExp)*bit[1,][i]
    total <- total + num
    currExp <- currExp + 1
  }
  return(total)
}

classifyLabelNumber <- function(num) {
  label <- numberMap[[as.character(num)]]
  if (is.null(label)) {
    return("undefined")
  }
  return(label)
}

##########################################

# Preparing data
prepareData <- function(data) {
  Xin <- trainDataSource[,2:40]
  Yin <- decodeClassLabels2(trainDataSource[,41])
  return(list(Xin, Yin))
}
##########################################

# Parse output

parseOutput <- function(yOut) {
  rows <- dim(yOut)[1]
  cols <- dim(yOut)[2]
  
  maxNum <- -2147483647
  minNum <- 2147483647

  for (i in 1:rows) {
    for (j in 1:cols) {
      if ((yOut[i,][j]) < minNum) {
        minNum <- yOut[i,][j]
      }
      
      if ((yOut[i,][j]) > maxNum) {
        maxNum <- yOut[i,][j]
      }
    }
  }
  
  meanNum <- (maxNum + minNum) / 2
  
  for (i in 1:rows) {
    for (j in 1:cols) {
      if ((yOut[i,][j]) < meanNum) {
        yOut[i,][j] <- 0
      } else {
        yOut[i,][j] <- 1
      }
    }
  }
  
  return(yOut)
}

##########################################

## Acuracia
bests <- list()

getAccuracy <- function(y, yhat) {
  total <- nrow(y)
  w <- 0
  
  for (i in 1:total) {
    yC <- classifyLabelNumber(bitToInt(t(as.matrix(y[i,]))))
    yhatC <- classifyLabelNumber(bitToInt(t(as.matrix(yhat[i,]))))
    if (yC != yhatC) {
      w <- w + 1
    }
  }
  return(1 - (w/total))
}

maxAcc <- -1

##########################################

nHidden <- 5
nExits<- 3

folds <- cut(seq(1,nrow(trainDataSource)),breaks=n_folds,labels=FALSE)

for(i in 1:n_folds){
  
  testIndexes <- which(folds==i,arr.ind=TRUE)
  testData <- trainDataSource[testIndexes, ]
  trainData <- trainDataSource[-testIndexes, ]
  
  trainDataList <- prepareData(trainData)
  xInTrain <-as.matrix(trainDataList[[1]])
  yInTrain <- trainDataList[[2]]
  
  testDataList <- prepareData(testData)
  xInTest <-as.matrix(testDataList[[1]])
  yInTest <- testDataList[[2]]
  
  retlist <- treinaMLP(xInTrain, yInTrain, eta, tol, maxepocas, nHidden, nExits)
  Z <- retlist[[1]]
  W <- retlist[[2]]
  
  xInTest <- cbind(xInTest, 1)
  
  retlistans <- YMLP(Z, W, xInTest, 1)
  yhat <- retlistans[[1]]
  parsedOut <- parseOutput(yhat)
  accuracy <- getAccuracy(yInTest,parsedOut)
  print(accuracy)
  if (accuracy > maxAcc) {
    maxAcc <- accuracy
    bests <- retlist
  }
}
rm(list = ls())
source("treinaMLP.R")
source("YMLP.R")
library(r2r)
library(ggplot2)

normalize <- function(x){
  (x - min(x)) / (max(x)-min(x))
}

trainDataSource <- read.csv("./dados/treino.csv", header = T)
testDataSource <- read.csv("./dados/validacao.csv", header = T)

tol<-0.01
eta<-0.1
maxepocas<-150

n_folds = 10

{
  ## Mapping labels
  labelMap <- hashmap()
  
  labelMap[["teens"]] = 0
  labelMap[["twenties"]] = 1
  labelMap[["thirties"]] = 2
  labelMap[["fourties"]] = 3
  labelMap[["fifties"]] = 4
  
  numberMap <- hashmap()
  
  numberMap[["0"]] = "teens"
  numberMap[["1"]] = "twenties"
  numberMap[["2"]] = "thirties"
  numberMap[["3"]] = "fourties"
  numberMap[["4"]] = "fifties"
}

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
  Xin <- (sapply(trainDataSource[,c(2:40)], normalize))*2-1
  Yin <- decodeClassLabels2(trainDataSource[,41])
  return(list(Xin, Yin))
}
##########################################

# Parse output

parseOutput <- function(yOut) {
  rows <- dim(yOut)[1]
  cols <- dim(yOut)[2]
  
  for (i in 1:rows) {
    for (j in 1:cols) {
      if ((yOut[i,][j]) >= 0.5) {
        yOut[i,][j] <- 1
      } else {
        yOut[i,][j] <- 0
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

acc<-matrix(0,nrow=n_folds)

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
  acc[i] <- accuracy
  print(accuracy)
  if (accuracy > maxAcc) {
    maxAcc <- accuracy
    bests <- retlist
  }
}

## Plots

barplot(t(acc), col="steelblue", main="Acuracia por fold", xlab="Fold", ylab="Acuracia", ylim = c(0,1))

## Validate

xValidation <- cbind(as.matrix((sapply(testDataSource[,c(2:40)], normalize))*2-1), 1)
validateRetlist <- YMLP(Z, W, xValidation, 1)
parsedOut <- parseOutput(validateRetlist[[1]])

labels <- matrix(nrow=nrow(parsedOut), ncol=1)

for (i in 1:nrow(parsedOut)) {
  label <- classifyLabelNumber(bitToInt(t(as.matrix(parsedOut[i,]))))
  labels[i] <- label
}

output <- as.data.frame(cbind(testDataSource[,1], labels))

colnames(output)[1]  <- "id"
colnames(output)[2]  <- "y"

write.csv(output,file='./dados/sample.csv', row.names=FALSE)


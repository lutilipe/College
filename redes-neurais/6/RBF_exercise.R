rm(list = ls())
source('RBFtrainer.R')
source('YRBF.R')
library('plot3D')

###############################
#Parâmetros dos dados
n1 = 200; m11 = -1; m12 = -1; s1 = 0.35;
n3 = 200; m31 =  1; m32 =  1; s3 = 0.35;

n2 = 200; m21 = 1; m22 = -1; s2 = 0.35;
n4 = 200; m41 = -1; m42 = 1; s4 = 0.35;

#Classe positiva#
Cp <- rbind(cbind(rnorm(n1,m11,s1), rnorm(n1,m12,s1)),
            cbind(rnorm(n3,m31,s3), rnorm(n3,m32,s3)))

#Classe negativa#
Cn <- rbind(cbind(rnorm(n2,m21,s2), rnorm(n2,m22,s2)), 
            cbind(rnorm(n4,m41,s4), rnorm(n4,m42,s4)))

Yp <- array(1,dim=c(n1+n3,1));
Yn <- array(-1,dim=c(n2+n4,1));

X = rbind(Cp,Cn)
Y = rbind(Yp,Yn)
FullData <- as.data.frame(cbind(X,Y))
FullData <- FullData[sample(nrow(FullData)),]

neuronNumber = 10
nFolds <- 10

acuracias <- matrix(nrow=nFolds, ncol=1)
acuraciaMedia <- 0
maiorAcuracia <- 0
maiorIndex <- 0

dataFolds <- cut(seq(1,nrow(FullData)), breaks=nFolds, labels=FALSE)
RBFmods <- rep(list(list()),10)

for(i in 1:nFolds){
  testIndexes <- which(dataFolds==i, arr.ind=TRUE)
  testData <- FullData[testIndexes,]
  trainData <- FullData[-testIndexes,]
  
  wt <- RBFtrainer(as.matrix(trainData[,c(1:2)]),trainData[,3],neuronNumber)
  RBFmods[[i]] <- append(RBFmods[[i]], wt)
  Yhat <- YRBF(as.matrix(testData[,c(1:2)]), RBFmods[[i]])
  yt <- (1*(Yhat >= 0) - 0.5)*2
  acuracias[i,] = 1 - ( t(as.matrix(testData[,3]) - yt) %*% (as.matrix(testData[,3]) - yt))/nrow(testData)
  if(acuracias[i,] > maiorAcuracia){
    maiorAcuracia <- acuracias[i,]
    maiorIndex <- i
  }
  acuraciaMedia <- acuraciaMedia + (acuracias[i,])/nFolds

}

########################################
#PLOT GRÁFICO
seqx1x2 <- seq(-3, 3, 0.05)
lseq <- length(seqx1x2)
MZ <- matrix(nrow=lseq, ncol=lseq)
cr <- 0
for(i in 1:lseq){
  for(j in 1:lseq){
    cr <- cr+1
    x1 <- seqx1x2[i]
    x2 <- seqx1x2[j]
    x1x2 <- matrix(cbind(x1,x2), nrow=1)
    MZ[i,j] <- YRBF(x1x2, RBFmods[[maiorIndex]])
  }
}

plotData1 <- FullData[FullData[,3]==1,]
plotData2 <- FullData[FullData[,3]==-1,]
library(RColorBrewer)
coul <- brewer.pal(9, "Pastel1")

image(MZ, useRaster = TRUE, axes = FALSE, col = coul[1:2], )
par(new=T)

plot(plotData1[,1],plotData1[,2],col='blue',pch=16,xlab = '' ,ylab= '', cex = 0.8, main = 'Problema XOR - RBF',
     xlim = c(-3,3),
     ylim = c(-3,3))
par(new=T)
plot(plotData2[,1],plotData2[,2],col='red',pch=16,xlab = '' ,ylab= '', cex = 0.8,
     xlim = c(-3,3),
     ylim = c(-3,3))

########################################
#PLOT ACURACIAS
print(acuracias)
print(acuraciaMedia)
print(maiorAcuracia)
print(maiorIndex)

# desvioPadrao <- sd(acuracias)
nomes <- as.character(c(1:10))
nomes <- append(nomes, "Média")
acuracias <- append(acuracias, acuraciaMedia)

library(RColorBrewer)
coul <- brewer.pal(10, "Set3")
coul2 <- brewer.pal(3, "Set3")
grid(nx=NA, ny=NULL)

seqi<-seq(0.06,6,0.06)
seqj<-seq(0.06,6,0.06)

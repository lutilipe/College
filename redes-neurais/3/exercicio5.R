rm(list=ls())
source('ELM.R')
source('YELM.R')
library("mlbench")
library('ggplot2')
library('RSNNS')

#Data loading
{
  NORMALS <- (mlbench.2dnormals(200))
  XOR     <- (mlbench.xor(400))
  CIRCLE  <- (mlbench.circle(100))
  SPIRAL  <- (mlbench.spirals(100,sd = 0.05))
}



#Parametros e plot
{
  table <- as.data.frame(XOR)
  
  X_IN <- as.matrix(table[, c(1:2)])
  Y_D  <- as.matrix((1*((table[, c("classes")])=='2')-0.5)*2)
  XY_all <- cbind(as.matrix(table[, c(1:2)]), as.matrix((1*((table[, c("classes")])=='2')-0.5)*2))
  
  table <- as.data.frame(XY_all)
  
  ggplot(table, aes(x=x.1, y=x.2, color=V3)) +
    geom_point(size=2) +
    theme_classic()

  neuronNumber <- 60
  plotrange <- 1
  plotname <- "XOR - 60 NEURONS"
}

XY_split <- splitForTrainingAndTest(XY_all[,c(1:2)], XY_all[,3], ratio = 0.3)

X_IN_train <- as.matrix(XY_split$inputsTrain)
Y_D_train <- as.matrix(XY_split$targetsTrain)

X_IN_teste <- as.matrix(XY_split$inputsTest)
Y_D_teste <- as.matrix(XY_split$targetsTest)

retlist <- ELMtrainer(X_IN_train, Y_D_train, neuronNumber, 1)
W <- retlist[[1]]
H <- retlist[[2]]
Z <- retlist[[3]]

Yhat_train <- YELM(X_IN_train, Z, W, 1)
e_train <- sum((Y_D_train-Yhat_train)^2)/4
print(e_train)

Yhat_t <- YELM(X_IN, Z, W, 1)
e_t <- sum((Y_D - Yhat_t)^2)/4
print(e_t)

acuracia <- 1-(t(Y_D - Yhat_t) %*% (Y_D - Yhat_t))/200
print(acuracia)

########################################
#plots
seqx1x2 <- seq(-plotrange, plotrange, 0.01)
lseq <- length(seqx1x2)
MZ <- matrix(nrow=lseq, ncol=lseq)
cr <- 0
for(i in 1:lseq){
  for(j in 1:lseq){
    cr <- cr+1
    x1 <- seqx1x2[i]
    x2 <- seqx1x2[j]
    x1x2 <- matrix(cbind(x1,x2), nrow=1)
    MZ[i,j] <- YELM(x1x2, Z, W, 1)
  }
}

plotData1 <- XY_all[XY_all[,3]==1,]
plotData2 <- XY_all[XY_all[,3]==-1,]
library(RColorBrewer)
coul <- brewer.pal(9, "Pastel1")

image(MZ, useRaster = TRUE, axes = FALSE, col = coul[1:2], )
par(new=T)

plot(plotData1[,1],plotData1[,2],col='blue',pch=16,xlab = '' ,ylab= '', cex = 1.3, main = plotname,
     xlim = c(-plotrange,plotrange),
     ylim = c(-plotrange,plotrange))
par(new=T)
plot(plotData2[,1],plotData2[,2],col='red',pch=16,xlab = '' ,ylab= '', cex = 1.3,
     xlim = c(-plotrange,plotrange),
     ylim = c(-plotrange,plotrange))

#contour2D(MZ,seqx1x2,seqx1x2,xlim = c(-plotrange,plotrange),ylim = c(-plotrange,plotrange),xlab = '' ,ylab= '',levels=0 )





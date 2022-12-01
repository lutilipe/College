rm(list = ls())
library(mlbench)
library("scatterplot3d") # load


sech2 <- function(u) {
  return (((2 / (exp(u)+exp(-u))) * (2/(exp(u) + exp(-u)))))
}

YMLP <- function(Zin, Win, Xin, add, case=0){
  Hs <- apply(Zin, 2, function(z,x) tanh(x%*%z), x=Xin)
  if(case==1){
    Hs <- t(Hs)
  }
  Hs <- cbind(Hs,add)
  Yhat <- tanh(Hs%*%Win)
  return(list(Yhat,Hs))
}

n = 100
dados <- mlbench.spirals(n,0.6)
plot(dados)


Xin<-dados$x

Yin<-(as.numeric(dados$classes)^2)-3


tol<-0.1
eta<-0.01
maxepocas<-1000



sech_squared <- function(x){
  return (((2/(exp(x)+exp(-x)))*(2/(exp(x)+exp(-x)))))
}

nHidden <- 3
nExits<- 1

  nCases <- dim(Xin)[1]
  nInputs <- dim(Xin)[2]
  
  Z <- matrix(runif((nInputs+1)*nHidden)-0.5, ncol=nHidden)
  W <- matrix(runif((nHidden+1)*nExits)-0.5, ncol=nExits)
  
  #Bias intermediário
  Xin <- cbind(Xin,1)
  
  nepocas<-0
  eepoca<-tol+1
  evec<-matrix(nrow=1,ncol=maxepocas)
  
  while ((nepocas < maxepocas) && (eepoca>tol)){ #eepocas erro da epoca e tol tolerancia
    ei2<-0
    #sequencia aleatoria para treinamento
    xseq<-sample(nCases)
    for (i in 1:nCases) {
      #padrao para sequencia aleatoria
      irand<-xseq[i]
      
      retlist <- YMLP(Z, W, Xin[irand,], 1, 1)

      Yhat_i <- retlist[[1]]
      Hs <- retlist[[2]]
      
      #erro = (y[iseq] – yhat)
      E_saidas <- Yin[irand] - Yhat_i
      dE_saidas <- E_saidas * (sech_squared(Hs%*%W))
      dE_intern <- (dE_saidas%*%t(head(W,-1)))*(sech_squared(t(Xin[irand,])%*%Z))
      
      #Atualiza pesos w
      W <- W + eta * t(Hs)%*%dE_saidas
      
      #Atualiza pesos z
      Z <- Z + eta * Xin[irand,]%*%dE_intern
      
      ei2 = ei2 + sum(E_saidas^2)
    }
    #numero de epocas
    nepocas<-nepocas+1
    evec[nepocas]<-ei2/nCases
    #erro por epoca
    eepoca<-evec[nepocas]
  }


plotrange <- 0.7

#plots
seqx1x2 <- seq(-plotrange, plotrange, 0.01)
lseq <- length(seqx1x2)
MZ <- matrix(nrow=lseq, ncol=lseq)

cr <- 0
a <- 0
H = matrix(nrow=lseq, ncol=3)
for(i in 1:lseq){
  for(j in 1:lseq){
    cr <- cr+1
    x1 <- seqx1x2[i]
    x2 <- seqx1x2[j]
    x1x2 <- matrix(cbind(x1,x2), nrow=1)
    x1x2 <- cbind(x1x2,1)
    
    retlist <- YMLP(Z, W, x1x2, 1, 1)
    MZ[i,j] <- retlist[[1]]
  }
  H[a,] <- retlist[[2]][,1:3]
  a<-a+1
}

library(RColorBrewer)
coul <- brewer.pal(9, "Set3")

image(MZ, useRaster = TRUE, axes = FALSE, col = coul[1:2], )
par(new=T)
plot(dados, xlim = c(-plotrange,plotrange), 
     ylim = c(-plotrange,plotrange))
scatterplot3d(H)

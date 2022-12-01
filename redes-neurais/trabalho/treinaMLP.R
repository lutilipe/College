source("functions.R")
library(e1071)

sech_squared <- function(x){
  return (((2/(exp(x)+exp(-x)))*(2/(exp(x)+exp(-x)))))
}

treinaMLP <- function(Xin, Yin, eta, tol, maxepocas, nHidden, nExits) {
  nCases <- dim(Xin)[1]
  nInputs <- dim(Xin)[2]
  
  Z <- matrix(runif((nInputs+1)*nHidden)-0.5, ncol=nHidden)
  W <- matrix(runif((nHidden+1)*nExits)-0.5, ncol=nExits)
  
  Xin <- cbind(Xin,1)

  nepocas<-0
  eepoca<-tol+1
  evec<-matrix(nrow=1,ncol=maxepocas)
  
  while ((nepocas < maxepocas) && (eepoca>tol)){
    ei2<-0

    xseq<-sample(nCases)
    for (i in 1:nCases) {
      irand<-xseq[i]
      
      retlist <- YMLP(Z, W, Xin[irand,], 1, 1)
      
      Yhat_i <- retlist[[1]]
      Hs <- retlist[[2]]
      E_saidas <- Yin[irand,] - Yhat_i
      
      dE_saidas <- E_saidas * (dsigmoid(Hs%*%W))
      dE_intern <- (dE_saidas%*%t(head(W,-1)))*(sech_squared(t(Xin[irand,])%*%Z))
      
      W <- W + eta * t(Hs)%*%dE_saidas
      
      Z <- Z + eta * Xin[irand,]%*%dE_intern
      
      ei2 = ei2 + E_saidas %*% t(E_saidas)
    }
    nepocas<-nepocas+1
    evec[nepocas]<-ei2/nCases
    eepoca<-evec[nepocas]
  }
  
  retlist<-list(Z,W,evec[1:nepocas])
  return(retlist)
}
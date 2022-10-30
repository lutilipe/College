library("corpcor")

ELMtrainer <- function(Xin, Yin, numNeuron, par){
  n <- dim(Xin)[2]

  if(par==1){
    Xin <- cbind(1,Xin)
    Z <- replicate(numNeuron, runif((n+1), -0.5, 0.5))
  }
  else Z <- replicate(numNeuron, runif(n, -0.5, 0.5))
  
  H <- tanh(Xin %*% Z)
  
  W <- pseudoinverse(H) %*% Yin
  
  return(list(W,H,Z))
}
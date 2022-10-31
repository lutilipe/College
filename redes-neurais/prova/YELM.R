YELM <- function(Xin, Z, W, par){
  
  n<-dim(Xin)[2]
  
  if(par==1){
    Xin <- cbind(1,Xin)
  }
  
  H <- tanh(Xin %*% Z)
  
  Yhat <- sign(H %*% W)
  
  return(Yhat)
}

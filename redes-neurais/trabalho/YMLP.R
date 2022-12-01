YMLP <- function(Zin, Win, Xin, add, case=0){
  Hs <- apply(Zin, 2, function(z,x) tanh(x%*%z), x=Xin)
  if(case==1){
    Hs <- t(Hs)
  }
  Hs <- cbind(Hs,add)
  Yhat <- tanh(Hs%*%Win)
  return(list(Yhat,Hs))
}

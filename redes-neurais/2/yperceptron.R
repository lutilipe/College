yperceptron <- function(x,w,p){
  tmp <- cbind(p,x)
  return(sign(tmp%*%w))
}
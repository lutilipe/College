yadaline <- function(x,w,p){
  temp <- cbind(p,x)
  return(temp%*%w);
}
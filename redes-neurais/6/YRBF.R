source('gaussianRadial.R')

YRBF <- function(Xin, mod){
  
  N <- dim(Xin)[1]
  n <- dim(Xin)[2]
  
  m <- as.matrix(mod[[1]])
  covlist <- mod[[2]]
  p <- length(covlist)
  W <- mod[[3]]
  
  Xin <- as.matrix(Xin)
  
  H <- matrix(nrow = N, ncol = p)
  
  for (j in 1:N){
    for (i in 1:p){
      mi <- m[i,]
      covi <- covlist[i]
      covi <- matrix(unlist(covlist[i]), ncol = n, byrow = T) + 0.001 * diag(n)
      H[j,i] <- gaussianRadial(Xin[j,], mi, covi, n)
    }
  }
  
  Haug <- cbind(1,H)
  Yhat <- Haug %*% W
  
  return(Yhat)
}
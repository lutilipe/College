source('gaussianRadial.R')

RBFtrainer <- function(Xin, Yin, p){

  N <- dim(Xin)[1]
  n <- dim(Xin)[2]
  
  Xin <- as.matrix(Xin)
  Yin <- as.matrix(Yin)
  
  xclust <- kmeans(Xin, p)
  
  m <- as.matrix(xclust$centers)
  covlist <- list()
  
  for (i in 1:p){
    ici <- which(xclust$cluster == i)
    xci <- Xin[ici,]
    if (n==1)
      covi <- var(xci)
    else covi <- cov(xci)
    covlist[[i]] <- covi
  }
  
  H <- matrix(nrow = N, ncol = p)
  
  for (j in 1:N){
    for (i in 1:p){
      mi <- m[i,]
      covi <- covlist[i]
      covi <- matrix(unlist(covlist[i]), ncol=n, byrow=T) + 0.001 * diag(n)
      H[j,i] <- gaussianRadial(Xin[j,], mi, covi, n)
    }
  }
  Haug <- H * 1/(max(as.numeric(unlist(H))))
  Haug <- cbind(1,Haug)
  W <- (solve(t(Haug) %*% Haug) %*% t(Haug)) %*% Yin
  
  return(list(m, covlist, W, H))
}
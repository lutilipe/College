softplus <- function(x, k=1) {
  return(log(1+exp(k*x)))
}

dsoftplus <- function(x, k=1) {
  return(1/(1+exp(-k*x)))
}

softmax <- function(par){
  n.par <- length(par)
  par1 <- sort(par, decreasing = TRUE)
  Lk <- par1[1]
  for (k in 1:(n.par-1)) {
    Lk <- max(par1[k+1], Lk) + log1p(exp(-abs(par1[k+1] - Lk))) 
  }
  val <- exp(par - Lk)
  return(val)
}

matrixDiag <- function(m) {
  newM <- matrix(0, ncol=ncol(m), nrow=ncol(m))
  for (i in 1:ncol(m)) {
    newM[i,][i] <- m[1,][i]
  }
  return(newM)
}

dsoftmax <- function(s){
  jacobian_m <- matrixDiag(s)
  
  for (i in 1:nrow(jacobian_m)) {
    for (j in 1:ncol(jacobian_m)) {
      if (i == j) {
        jacobian_m[i,][j] <- s[i] * (1-s[i])
      } else {
        jacobian_m[i,][j] <- -s[i]*s[j]
      }
    }
  }
  print(jacobian_m)
  return(jacobian_m)
  
}

softmax(matrix(c(1,2),nrow=1))
dsoftmax(softmax(matrix(c(1,2),nrow=1)))

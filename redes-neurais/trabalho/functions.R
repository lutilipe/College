softplus <- function(x, k=1) {
  return(log(1+exp(k*x)))
}

dsoftplus <- function(x, k=1) {
  return(1/(1+exp(-k*x)))
}
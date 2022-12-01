gaussianRadial <- function(x, m, K, n){
  
  if (n==1) {
    r <- sqrt(as.numeric(K))
    px <- (1/(sqrt(2*pi*r*r)))*exp(-0.5 * ((x-m)/(r))^2)
  }
  else px <- ((1/(sqrt((2*pi)^n*(det(K)))))*exp(-0.5*(t(x-m) %*% (solve(K)) %*% (x-m))))
  
  return(px)
}
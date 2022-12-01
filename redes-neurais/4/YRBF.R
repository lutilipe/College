YRBF <-function(xin, modRBF) {
  gauss <- function(x,m,s){
    return(exp(-0.5*(rowSums((x-m)^2))/(s^2)))
  }
  N<-dim(xin)[1]
  n<-dim(xin)[2]
  m<-as.matrix(modRBF[[1]])
  covlist<-modRBF[[2]]
  p<-length(covlist)
  W<-modRBF[[3]]
  
  xin<-as.matrix(xin)
  H<-matrix(nrow=N, ncol=p)
  
  for (j in 1:N) {
    for (i in 1:p) {
      mi<-m[i,]
      covi<-covlist[i]
      covi<-matrix(unlist(covlist[i]), ncol=n, byrow = T) + 0.001 * diag(n)
      H[j,i]<-gauss(xin[j,], mi, covi)
    }
  }
  
  Haug<-cbind(1,H)
  Yhat<-Haug %*% W
  return(Yhat)
}
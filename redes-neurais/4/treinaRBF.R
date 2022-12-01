library('caret')

treinaRBF <- function(xin, yin, p) {
  gauss <- function(x,m,s){
    return(exp(-0.5*(rowSums((x-m)^2))/(s^2)))
  }
  
  N<-dim(xin)[1]
  n<-dim(xin)[2]
  
  xin<-as.matrix(xin)
  yin<-as.matrix(yin)
  
  xclust<-kmeans(xin,p)
  m<-as.matrix(xclust$centers)
  covlist <- list()
  
  for (i in 1:p) {
    ici<-which(xclust$cluster == i)
    xci<-xin[ici,]
    if (n == 1) covi<-var(xci)
    else covi <- cov(xci)
    covlist[[i]] <- covi
  }
  
  H<-matrix(nrow=N, ncol = p)
  for (j in 1:N) {
    for (i in 1:p) {
      mi<-m[i,]
      covi<-covlist[i]
      covi<-matrix(unlist(covlist[i]), ncol=n, byrow =T) + 0.001 * diag(n)
      H[j,i]<-gauss(xin[j,],mi,covi)
      
    }
  }
  
  Haug <-cbind(1,H)
  W<-(solve(t(Haug) %*% Haug) %*% t(Haug)) %*% yin
  
  return(list(m,covlist,W,H))
}
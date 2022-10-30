
##############################################
# problema de classificação
rm(list=ls())
source('treinaperceptron.R')
source('yperceptron.R')
library('plot3D')


n1 = 200
m11 = 2; 
m12 = 2; 
s1 = 0.4;

n2 = 200; m21 = 4; m22 = 4; s2 = 0.4;

##c11 <- runif(n1,2);
##c12 <- runif(n1);
##c1 <- c(c11,c12):

##rep(t(m2),times=4)
## Z <- array(m1, dim=c(4,2)) - funciona como ones, zeros e repmat


c11 = rnorm(n1,m11,s1);
c12 = rnorm(n1,m12,s1);
c21 = rnorm(n2,m21,s2);
c22 = rnorm(n2,m22,s2);

Cp <- cbind(c11, c12) ##%classe positiva
Cn <- cbind(c21, c22) ##%classe negativa

y1 <- array(1,dim=c(n1,1));
y2 <- array(-1,dim=c(n2,1));

Yp = y1;
Yn = y2; 



X = rbind(Cp,Cn)
Y = rbind(Yp,Yn)

plot(Cp[,1],Cp[,2],col='red',pch='o', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
plot(Cn[,1],Cn[,2],col='blue',pch='+', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))


eta<-0.01
tol<-0.001
mxepoc<-200



retlist<-treinaperceptron(X,Y,eta,tol,mxepoc,1)



w<-retlist[[1]]
##w<-rbind(-6,1,1)

erro<-retlist[[2]]


Yhat = yperceptron(X,w,1)




plot(erro,type='l', xlab="Época")

#separação
seqi<-seq(0.06,6,0.06)
seqj<-seq(0.06,6,0.06)

M <- matrix(0,nrow=length(seqi),ncol=length(seqj)) 
ci<-0
for (i in seqi){
  ci<-ci+1
  cj<-0
  for(j in seqj)
  {
    cj<-cj+1
    M[ci,cj]<- yperceptron(cbind(i,j),w,1)
    
  }
}

plot(Cp[,1],Cp[,2],col='red',pch='o', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
plot(Cn[,1],Cn[,2],col='blue',pch='+', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
contour2D(M,seqi,seqj,xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])),xlab = '' ,ylab= '',levels=0 )

persp3D(seqi,seqj,M,counter=T,theta = 55, phi = 30, r = 40, d = 0.1, expand = 0.5,
        ltheta = 90, lphi = 180, shade = 0.4, ticktype = "detailed", nticks=5)


# variando tamanho do conjunto de treinamento
idx = sample(n1+n2)
tam = 10
Xtrain = X[idx[1:tam],]   
Ytrain = Y[idx[1:tam],]
retlist<-treinaperceptron(Xtrain,Ytrain,eta,tol,mxepoc,1)



w<-retlist[[1]]
#w<-rbind(-6,1,1)

erro<-retlist[[2]]


Yhat = yperceptron(X,w,1)




plot(erro,type='l', xlab="Época")

#separação
seqi<-seq(0.06,6,0.06)
seqj<-seq(0.06,6,0.06)

M <- matrix(0,nrow=length(seqi),ncol=length(seqj)) 
ci<-0
for (i in seqi){
  ci<-ci+1
  cj<-0
  for(j in seqj)
  {
    cj<-cj+1
    M[ci,cj]<- yperceptron(cbind(i,j),w,1)
    
  }
}

plot(Cp[,1],Cp[,2],col='red',pch='o', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
plot(Cn[,1],Cn[,2],col='blue',pch='+', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
plot(Xtrain[,1],Xtrain[,2],col='green',pch='0', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)

contour2D(M,seqi,seqj,xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])),xlab = '' ,ylab= '',levels=0 )

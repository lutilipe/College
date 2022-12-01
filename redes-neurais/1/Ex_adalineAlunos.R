
##############################################
# problema de classificação
rm(list=ls())
source('trainadaline.R')
source('yadaline.R')
library('plot3D')


n1 = 250; m11 = 2; m12 = 4; s1 = 0.3;
n3 = 250; m31 = 4; m32 = 2; s3 = 0.3;

n2 = 250; m21 = 4; m22 = 4; s2 = 0.3;
n4 = 250; m41 = 2; m42 = 2; s4 = 0.3;


##c11 <- runif(n1,2);
##c12 <- runif(n1);
##c1 <- c(c11,c12):

##rep(t(m2),times=4)
## Z <- array(m1, dim=c(4,2)) - funciona como ones, zeros e repmat


c11 = rnorm(n1,m11,s1);
c12 = rnorm(n1,m12,s1);
c31 = rnorm(n3,m31,s3);
c32 = rnorm(n3,m32,s3);

c21 = rnorm(n2,m21,s2);
c22 = rnorm(n2,m22,s2);
c41 = rnorm(n4,m41,s4);
c42 = rnorm(n4,m42,s4);

Cpaux1 <- cbind(c11, c12) ##%classe positiva
Cpaux2 <- cbind(c31, c32)
Cp <- rbind(Cpaux1, Cpaux2)
Cnaux1 <- cbind(c21, c22) ##%classe negativa
Cnaux2 <- cbind(c41, c42)
Cn <- rbind(Cnaux1, Cnaux2)

y1 <- array(1,dim=c(n1+n3,1));
y2 <- array(-1,dim=c(n2+n4,1));

Yp = y1;
Yn = y2; 



X = rbind(Cp,Cn)
Y = rbind(Yp,Yn)

plot(Cp[,1],Cp[,2],col='red',pch='o', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
plot(Cn[,1],Cn[,2],col='blue',pch='+', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
#par(new=T)
#plot(Cp[,3],Cp[,4],col='red',pch='o', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
#par(new=T)
#plot(Cn[,3],Cn[,4],col='blue',pch='+', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))

eta<-0.01
tol<-0.01
mxepoc<-200



retlist<-trainadaline(X,Y,eta,tol,mxepoc,1)



w<-retlist[[1]]

erro<-retlist[[2]]


Yhat = yadaline(X,w,1)




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
    M[ci,cj]<- yadaline(cbind(i,j),w,1)
    
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
idx = sample(n1+n2+n3+n4)
tam = (n1+n2+n3+n4)*0.1
Xtrain = X[idx[1:tam],]
Ytrain = Y[idx[1:tam],]

retlist<-trainadaline(Xtrain,Ytrain,eta,tol,mxepoc,1)



w<-retlist[[1]]

erro<-retlist[[2]]


Yhat = yadaline(X,w,1)




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
    M[ci,cj]<- yadaline(cbind(i,j),w,1)
    
  }
}

plot(Cp[,1],Cp[,2],col='green',pch='o', xlim = c(0,6),ylim = c(0,6),xlab = '' ,ylab= '')
par(new=T)
plot(Cn[,1],Cn[,2],col='blue',pch='+', xlim = c(0,6),ylim = c(0,6),xlab = '' ,ylab= '')
par(new=T)
plot(Xtrain[,1],Xtrain[,2],col='red',pch='0', xlim = c(0,6),ylim = c(0,6),xlab = '' ,ylab= '')
par(new=T)

contour2D(M,seqi,seqj,xlim = c(0,6),ylim = c(0,6),xlab = '' ,ylab= '',levels=0 )
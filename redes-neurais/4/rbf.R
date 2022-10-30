rm(list=ls())
library('corpcor')

gauss <- function(x,m,s){
  return(exp(-0.5*(rowSums((x-m)^2))/(s^2)))
}

n1 = 250; m11 = 2; m12 = 4; s1 = 0.3;
n3 = 250; m31 = 4; m32 = 2; s3 = 0.3;

n2 = 250; m21 = 4; m22 = 4; s2 = 0.3;
n4 = 250; m41 = 2; m42 = 2; s4 = 0.3;



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


X = rbind(Cp,Cn)

y1 <- array(1,dim=c(n1,1));
y2 <- array(1,dim=c(n3,1));
y3 <- array(-1,dim=c(n2,1));
y4 <- array(-1,dim=c(n4,1));


X = rbind(Cp,Cn)
Y = rbind(y1,y2,y3,y4)

plot(Cp[,1],Cp[,2],col='red',pch='o', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
plot(Cn[,1],Cn[,2],col='blue',pch='+', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))

m1 <- cbind(m11, m12)
m2 <- cbind(m31, m32)
m3 <- cbind(m21, m22)
m4 <- cbind(m41, m42)

m1 <- array(m1,dim=c(n1,2))
m2 <- array(m2,dim=c(n3,2))
m3 <- array(m3,dim=c(n2,2))
m4 <- array(m4,dim=c(n4,2))



h1 <- gauss(Cp[,1], m1,1)
h2 <- gauss(Cp[,2], m2, 1)
h3 <- gauss(Cn[,1], m3, 1)
h4 <- gauss(Cn[,2], m4, 1)

H <- cbind(h1, h2, h3, h3, 1)
w <- pseudoinverse(H) %*% Y

yhat <- H %*% Y


par(new=T)
plot(Cp[,1][which(yhat>0)],Cp[,2][which(yhat>0)], pch='*',col='blue',xlim=c(0,5),ylim=c(0,5),xlab='',ylab='')
par(new=T)
plot(Cn[,1][which(yhat<0)],Cn[,2][which(yhat<0)], pch='*',col='green',xlim=c(0,5),ylim=c(0,5),xlab='',ylab='')

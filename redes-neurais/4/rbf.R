rm(list=ls())
library('corpcor')
source('treinaRBF.R')
source('YRBF.R')

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

Cpaux1 <- rbind(c11, c12) ##%classe positiva
Cpaux2 <- rbind(c31, c32)
Cp <- cbind(Cpaux1, Cpaux2)
Cnaux1 <- rbind(c21, c22) ##%classe negativa
Cnaux2 <-rbind(c41, c42)
Cn <- cbind(Cnaux1, Cnaux2)


y1 <- array(1,dim=c(n1,1));
y2 <- array(1,dim=c(n3,1));
y3 <- array(-1,dim=c(n2,1));
y4 <- array(-1,dim=c(n4,1));


X = rbind(Cp,Cn)
Y = rbind(y1,y2,y3,y4)

plot(Cp[,1],Cp[,2],col='red',pch='o', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))
par(new=T)
plot(Cn[,1],Cn[,2],col='blue',pch='+', xlim = c(0,max(Cp[,1],Cn[,1])),ylim = c(0,max(Cp[,2],Cn[,2])))

n_folds<-10

allData<-X[sample(nrow(X)),]

# Randomiza data
folds <- cut(seq(1,nrow(allData)),breaks=n_folds,labels=FALSE)

numNerons <- 10
# Validacao cruzada
for(i in 1:n_folds){
  
  testIndexes <- which(folds==i,arr.ind=TRUE)
  testData <- allData[testIndexes, ]
  trainData <- allData[-testIndexes, ]
  
  xInTrain <-as.matrix(trainData[1:4])
  yInTrain <- as.matrix(trainData[5])
  
  xInTest <-as.matrix(testData[1:4])
  yInTest <- as.matrix(testData[5])
  
  modRBF <- treinaRBF(xInTrain, yInTrain, numNerons)
  W <- retlist[[3]]
  H <- retlist[[4]]
  
  yhat <- YRBF(xInTest, modRBF)
  acuracia <- mean(yhat==yInTest)
  y[i] = acuracia
  
  par(new=T)
  plot(Cp[,1][which(yhat>0)],Cp[,2][which(yhat>0)], pch='*',col='blue',xlim=c(0,5),ylim=c(0,5),xlab='',ylab='')
  par(new=T)
  plot(Cn[,1][which(yhat<0)],Cn[,2][which(yhat<0)], pch='*',col='green',xlim=c(0,5),ylim=c(0,5),xlab='',ylab='')
}
#


library("mlbench")
library(ggplot2)
source('ELMtrainer.R')
source('YELM.R')

# Carrega o arquivo de dados em um data frame
data <- read.csv("iris.data", header = FALSE)

# Header do dataframe
colnames(data) <-
  c("Sepal.Length",
    "Sepal.Width",
    "Petal.Length",
    "Petal.Width",
    "Species")

g <- ggplot(data=data, aes(x = Petal.Length, y = Petal.Width))
g <-g + 
  geom_point(aes(color=Species, shape=Species)) +
  xlab("Petal Length") +
  ylab("Petal Width") +
  ggtitle("Petal Length-Width")
print(g)

g <- ggplot(data=data, aes(x = Sepal.Length, y = Sepal.Width))
g <-g + 
  geom_point(aes(color=Species, shape=Species)) +
  xlab("Sepal Length") +
  ylab("Sepal Width") +
  ggtitle("Sepal Length-Width")
print(g)

# Remove classe Iris-setosa
rowRange <- 51:150

xAll <- data[rowRange, 1:4]
yAll <- (1*(data$Species[rowRange] == 'Iris-versicolor') -0.5)  *2

allData <- cbind(xAll[1:4], yAll);

yCol <- 5
xCol <- 1:4

n_folds<-5

allData<-allData[sample(nrow(allData)),]

# Randomiza data
folds <- cut(seq(1,nrow(allData)),breaks=n_folds,labels=FALSE)

y<-matrix(0,nrow=n_folds)

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
  
  retlist <- ELMtrainer(xInTrain, yInTrain, numNerons, 1)
  W <- retlist[[1]]
  H <- retlist[[2]]
  Z <- retlist[[3]]
  
  yhat <- YELM(xInTest, Z, W, 1)
  acuracia <- mean(yhat==yInTest)
  y[i] = acuracia
}
# 
desvio <- sd(y)
print(y)
print(desvio)
print(mean(y))


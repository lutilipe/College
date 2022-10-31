library("caret")

#load data from CSV file
data <- read.csv("iris.data", header=FALSE) 
#Set data frame column names 
colnames(data) <- c("Sepal.Length", "Sepal.Width", "Petal.Length", "Petal.Width", "Species")

# Split data into train/test sets using createDataPartition()
data_split <- createDataPartition(data$Species, p = 0.8, list = FALSE)

test <- data[-data_split,] # Save 20% of data for test validation here
dataset <- data[data_split,] # 80% of data 

# Data summary

# Dataset dimensions
dim(dataset)

# List of types for attributes
sapply(dataset, class)

# df header, just like python df.head() method
head(dataset)

# List of y class levels
levels(dataset$Species)

# ML Algorithm Evaluation
# Algorithms will be assessed using 10-fold crossvalidation, setup here
control <- trainControl(method="cv", number=10)
metric <- "Accuracy"

# build models

# Support Vector Machines
set.seed(7)
fit.svm <- train(Species~., data=dataset, method="kmeans", metric=metric, trControl=control)

# Summarize model accuracies
results <- resamples(list(svm=fit.svm))
summary(results)

dotplot(results)

# Best Model Summary
print(fit.lda)

# Evaluate LDA model on test data
predictions <- predict(fit.lda, test)
confusionMatrix(predictions, test$Species)

# To add: hyperparameter tuning to improve model best fit model score 


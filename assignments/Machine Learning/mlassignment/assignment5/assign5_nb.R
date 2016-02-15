news <- read.csv(file = "OnlineNewsPopularity.csv", header = TRUE)

drop_column <- c("url", "timedelta")
x <- news[,!(names(news) %in% drop_column)]
train <- 1:30000
test <- 30001:39644

x_train <- x[train,]
x_test <- x[test,]
x_train$shares <- ifelse(x_train$shares > 1400,1,0)
x_test$shares <- ifelse(x_test$shares > 1400,1,0)

y <- news[,"shares",drop=TRUE]
y_bin <- ifelse(y > 1400,1,0)

y_train <- y_bin[train]
y_test <- y_bin[test]

library("e1071", lib.loc="/usr/local/lib/R/site-library")
model_nb <- naiveBayes(shares ~ ., data = x_train)
prednb <- predict(model_nb, x_train)
prednb_test <- predict(model_nb, x_test)

acctrain_nb <- sum(prednb == x_train$shares) / 30000 * 100
acctest_nb <- sum(prednb_test == x_test$shares) / 30000 * 100

prectrain_nb <- sum(prednb_norm) / 30000 * 100
prectest_nb <- sum(prednb_testnorm) / 9644 * 100

rectrain_nb <- sum(prednb_norm[y_train == 1] == 1) / sum(y_train) * 100
rectest_nb <- sum(prednb_testnorm[y_test == 1] == 1) / sum(y_test) * 100

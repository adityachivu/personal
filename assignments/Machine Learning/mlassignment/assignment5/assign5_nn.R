news <- read.csv(file = "OnlineNewsPopularity.csv", header = TRUE)

drop_column <- c("url", "timedelta", "shares")
x <- news[,!(names(news) %in% drop_column)]
train <- 1:30000
test <- 30001:39644


x_train <- x[train,]
x_test <- x[test,]

y <- news[,"shares",drop=TRUE]
y_bin <- ifelse(y > 1400,1,0)

y_train <- y_bin[train]
y_test <- y_bin[test]


library("nnet", lib.loc="/usr/lib/R/library")
model_nn <- nnet(x_train, y_train, size = 5, decay = 1, maxiter = 500)
prednn <- predict(model_nn, data = x_train)
prednn_norm <- ifelse(prednn >= 0.5,1,0)

prednn_test <- predict(model_nn, x_test)
prednn_testnorm <- ifelse(prednn_test >= 0.5,1,0)

acctrain_nnet <- (sum(prednn_norm == y_train))/30000 * 100
acctest_nnet <- (sum(prednn_testnorm == y_test))/9644 * 100

prectrain_nnet <- sum(prednn_norm) / 30000 * 100
prectest_nnet <- sum(prednn_testnorm) / 9644 * 100

rectrain_nnet <- sum(prednn_norm[y_train == 1] == 1) / sum(y_train) * 100
rectest_nnet <- sum(prednn_testnorm[y_test == 1] == 1) / sum(y_test) * 100

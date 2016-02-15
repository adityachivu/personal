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


library("rpart", lib.loc="/usr/lib/R/library")
library("RColorBrewer", lib.loc="/usr/local/lib/R/site-library")
library("rpart.plot", lib.loc="/usr/local/lib/R/site-library")
library("tree", lib.loc="/usr/local/lib/R/site-library")
drop_column2 <- c("url", "timedelta")
x_dt <- news[,!(names(news) %in% drop_column2)]
x_dt$shares <- as.factor(ifelse(x_dt$shares > 1400,1,0))
model_dt1 <- rpart(shares ~ ., data = x_dt[train,])

preddt_norm <- ifelse(predict(model_dt1, data = x_dt[train,]) >= 0.5,1,0)
preddt_testnorm <- ifelse(predict(model_dt1, x[test,]) >= 0.5,1,0)

acctrain_dt = (sum(preddt_norm[,2] == y_train))/30000 * 100
acctest_dt = (sum(preddt_testnorm[,2] == y_test))/9644 * 100

prectrain_dt <- sum(preddt_norm[,2]) / 30000 * 100
prectest_dt <- sum(preddt_testnorm[,2]) / 9644 * 100

rectrain_dt <- sum(preddt_norm[y_train == 1,2] == 1) / sum(y_train) * 100
rectest_dt <- sum(preddt_testnorm[y_test == 1,2] == 1) / sum(y_test) * 100


#
#model_dt2 <- tree(shares ~ ., data = x_dt[train,])
#
#preddt_norm2 <- ifelse(predict(model_dt2, data = x_dt[train,]) >= 0.5,1,0)
#preddt_testnorm2 <- ifelse(predict(model_dt2, x[test,]) >= 0.5,1,0)

#acctrain_dt2 = (sum(preddt_norm2[,2] == y_train))/30000 * 100
#acctest_dt2 = (sum(preddt_testnorm2[,2] == y_test))/9644 * 100

#plot(model_dt2)
#text(model_dt2)



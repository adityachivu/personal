library("e1071", lib.loc="/usr/local/lib/R/site-library")

img <- c("")
y <- c("")

img <- readChar("/home/aditya/Data Science/mlassignment/trainingimages", 29*28*5000)
y <- readChar("/home/aditya/Data Science/mlassignment/traininglabels", 2*5000)
testimg<- readChar("/home/aditya/Data Science/mlassignment/testimages",29*28*1000)

img <- unlist(strsplit(img, ""))
y <- as.factor(as.numeric(unlist(strsplit(y, "\n"))))
testimg <- unlist(strsplit(testimg, ""))

img <- replace(img,img=='#',1)
img <- replace(img,img=='+',1)
img <- replace(img,img==' ',0)
img <- replace(img,img=='/r',0)
img <- replace(img,img=='/n',0)
img <- as.numeric(img)
dim(img) <- c(29,140000)
img <- t(img)
img <- img[,-29:-30]
img <- t(img)
dim(img) <- c(784,5000)
x <- t(img)

x_test <- unlist(strsplit(testimg,""))
x_test <- replace(x_test,x_test=='#',1)
x_test <- replace(x_test,x_test=='+',1)
x_test <- replace(x_test,x_test==' ',0)
x_test <- replace(x_test,x_test=='/r',0)
x_test <- replace(x_test,x_test=='/n',0)
x_test <- as.numeric(x_test)
dim(x_test) <- c(29,28000)
x_test <- t(x_test)
x_test <- x_test[,-29]
x_test <- t(x_test)
dim(x_test) <- c(784,1000)
x_test <- t(x_test)

model <- naiveBayes(x, y, 1)

y_pred <- predict(model ,x_test)
y_test <- readChar("/home/aditya/Data Science/mlassignment/testlabels",2*5000)
y_test <- strsplit(y_test,"\n")
y_test <- unlist(y_test)
y_test <- as.numeric(y_test)
y_test <- as.factor(y_test)

accuracy <- sum( y_pred == y_test)
accuracy <- (accuracy*100) /1000


sink("/home/aditya/Data Science/mlassignment/testlabels_generated.txt")
for(i in 1:1000){cat(i); cat(" "); cat(as.numeric(y_pred[i])-1); cat("\n")}
sink()

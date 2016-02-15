setwd("/home/aditya/gitfolder/personal/assignments/IR Project/collaborativefiltering")

library(recommenderlab)
library(reshape2)

tr <- read.csv("training_data.csv", header = TRUE)
head(tr)

g <- acast(tr, user ~ movie)

class(g)

R <- as.matrix(g)

r <- as(R, "realRatingMatrix")

r_m <- normalize(r, method = "Z-score")

rec <- Recommender(r[1:nrow(r)], method = "POPULAR")
rec

pre <- predict(rec, r[1:3], n=2)
pre

pre <- as(pre, "list")
pre

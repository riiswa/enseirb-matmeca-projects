
install.packages("readxl")
library("readxl")
install.packages("ggplot2")
library("ggplot2")
install.packages("dplyr")
library(dplyr)
install.packages("tidyr")
library(tidyr)
install.packages("patchwork")
library(patchwork)
install.packages("reshape2")
library(reshape2)
install.packages("corrplot")
library(corrplot)
install.packages("ggthemes") 
library(ggthemes)
install.packages("purrr") 
library(purrr)
install.packages(c("FactoMineR", "factoextra"))
library("FactoMineR")
library("factoextra")
install.packages("visdat")
library(visdat)
install.packages("cluster")
library(cluster)
theme_set(theme_hc())

df <- read_excel("Liste_Titanic.xlsx")
df <-  df %>% select(0:11) #retirer colonnes de fin inutiles
str(df)

vis_dat(df)

summary(df)

ggplot(df %>% count(survived, sex) %>% 
         mutate(pct=n/sum(n),               
                ypos = cumsum(n) - 0.5*n),
       aes(survived, n, fill=sex)) +
  geom_bar(stat="identity") +
  ggtitle("Survivors repartion by sex") 

ggplot() +
geom_density(data=df %>% filter(survived == 1), aes(x=age, color="survived")) +
geom_density(data=df %>% filter(survived == 0), aes(x=age, color="dead"))  +
  ggtitle("Suvivors repartion by age") 

ggplot(df %>% count(survived, pclass) %>% 
         mutate(pct=n/sum(n),               
                ypos = cumsum(n) - 0.5*n),
       aes(survived, n, fill=pclass)) +
  geom_bar(stat="identity") +
  ggtitle("Suvivors repartion by pclass") 

ggplot(df %>% count(survived, embarked) %>% 
         mutate(pct=n/sum(n),               
                ypos = cumsum(n) - 0.5*n),
       aes(survived, n, fill=embarked)) +
  geom_bar(stat="identity") +
  ggtitle("Suvivors repartion by embarkation") 

ggplot() +
geom_density(data=df %>% filter(survived == 1), aes(x=fare, color="survived")) +
geom_density(data=df %>% filter(survived == 0), aes(x=fare, color="dead"))  +
  ggtitle("Suvivors repartion by fare") 

missing.values <- df %>%
    gather(key = "key", value = "val") %>%
    mutate(is.missing = is.na(val)) %>%
    group_by(key, is.missing) %>%
    summarise(num.missing = n()) %>%
    filter(is.missing==T) %>%
    select(-is.missing) %>%
    arrange(desc(num.missing)) 
missing.values

vis_miss(df)

Median <- median(df$age, na.rm = TRUE)
print("The median is:")
print(Median)
df$age[is.na(df$age)] <- Median

Mean <- mean(df$fare, na.rm = TRUE)
print("The mean is:")
print(Mean)
df$fare[is.na(df$fare)] <- Mean

MostPresentValue <- tail(names(sort(table(df$embarked))), 1)
print("L'embarquation la plus présente est:")
print(MostPresentValue)
df$embarked[is.na(df$embarked)] <- MostPresentValue

df$cabin <- NULL 

vis_miss(df)

smp_size <- floor(0.50 * nrow(df))

## set the seed to make your partition reproducible
set.seed(123)
train_ind <- sample(seq_len(nrow(df)), size = smp_size)

train <- df[train_ind, ]
test <- df[-train_ind, ]

isSurvived <- function(x) {
    return(as.integer(x == 1))
} 

isDied <- function(x) {
    return(as.integer(!isSurvived(x)))
}

isMale <- function(x) {
    return(as.integer(x == "male"))
} 

isFemale <- function(x) {
    return(as.integer(!isMale(x)))
}

isClass1 <- function(x) {
    return(as.integer(x == 1))
} 

isClass2 <- function(x) {
    return(as.integer(x == 2))
} 

isClass3 <- function(x) {
    return(as.integer(x == 3))
} 

isChild <- function(x) {
    return(as.integer(x <= 15))
} 

isYoungAdult <- function(x) {
    return(as.integer(x > 15 && x <= 30))
} 

isAdult <- function(x) {
    return(as.integer(x > 30 && x <= 50))
} 

isOld <- function(x) {
    return(as.integer(x > 50))
}

completeDisjunctiveTable <- function(data) {
    cdt <- data.frame(
        male=sapply(data$sex, isMale),
        female=sapply(data$sex, isFemale),
        class1=sapply(data$pclass, isClass1),
        class2=sapply(data$pclass, isClass2),
        class3=sapply(data$pclass, isClass3),
        child=sapply(data$age, isChild),
        youngAdult=sapply(data$age, isYoungAdult),
        adult=sapply(data$age, isAdult),
        old=sapply(data$age, isOld),
        survived=sapply(data$survived, isSurvived),
        died=sapply(data$survived, isDied)
    )
    rownames(cdt) <- paste(seq.int(nrow(data)), data$name)
    return(cdt)
}

cdt <- completeDisjunctiveTable(train)
head(cdt)

vis_cor(cdt)

computeBurtValue <- function (x, y) {
    return(Reduce("+", 1:length(x) %>%
      map(function(i) x[i] * y[i])))
}

burtTable <- function(data) {
    bt = data.frame(matrix(vector(), ncol(data), ncol(data),
                dimnames=list(c(), colnames(data))),
                stringsAsFactors=F)
    for (i in colnames(data)){
        newCol <- vector()
        for (j in colnames(data)){
            newCol <- c(newCol, computeBurtValue(data[[i]], data[[j]]))
        }
        bt[[i]] <- newCol
    }
    rownames(bt) <- colnames(data)
    return(bt)
}          

bt <- burtTable(cdt)
bt

heatmap(as.matrix(bt))

btBis <- head(bt[1:(length(bt)-2)], -2)
btBis

btBis.ca <- CA(btBis, graph = FALSE)
btBis.ca

eigen1 <- get_eigenvalue(btBis.ca)
eigen1

p = 1/nrow(eigen1)
bp1 <- ggplot(data=as.data.frame(eigen1), aes(x=rownames(eigen1), y=eigenvalue)) +
  geom_bar(stat="identity") + geom_hline(yintercept = p, linetype = 'dashed', col = 'red', size = 2)
bp1

interp <- as.data.frame(round(cbind(btBis.ca$row$coord[,1:2],btBis.ca$row$contrib[,1:2],btBis.ca$row$cos2[,1:2]),2))
interp

plot.CA(btBis.ca)

btBis$km <-kmeans(interp[1:2], 3)
btBis$km

clusplot(interp[1:2], btBis$km$cluster, color=TRUE, shade=TRUE, 
         labels=2, lines=0)

bt.ca <- CA(bt, graph = FALSE, col.sup = 10:11)
eigen2<- get_eigenvalue(bt.ca)
 interp <- as.data.frame(round(cbind(bt.ca$row$coord[,1:2],bt.ca$row$contrib[,1:2],bt.ca$row$cos2[,1:2]),2))

km <-kmeans(interp[1:2], 3)
km

clusplot(interp[1:2], km$cluster, color=TRUE, shade=TRUE, 
         labels=2, lines=0)

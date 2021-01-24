setwd("E:/ECG project/ECG/Data")
meanPeaks <- function(x){
  graph<-read.table(paste('TXT/',x, sep=""))
  peaks<-read.table(paste('RPeaks/',x, sep=""))
  vector=c()
  for (i in 1:(length(peaks[,1])-1)){
    # print(peaks[,1][i])
    vector[i] <- (peaks[,1][i+1]-peaks[,1][i])
  }
  print(vector)
  print(mean(vector))
  }
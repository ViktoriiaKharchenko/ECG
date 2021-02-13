setwd("E:/ECG project/ECG/Data")
impose <- function(x){
    graph<-read.table(paste('TXTFiltered/',x, sep=""))
    peaks<-read.table(paste('RPeaks/',x, sep=""))
    m = matrix()
    vector=c()
    for (i in 1:(length(peaks[,1])-1)){
      # print(peaks[,1][i])
      vector[i] <- (peaks[,1][i+1]-peaks[,1][i])
    }
    sorted <- sort(vector)
    maxLenght <-sorted[length(sorted)]
    plot(graph$V1[1:maxLenght], type = "n")
    #print(peaks[1,])
    j=1
    for(i in 1:(length(peaks[,1])-1)){
      #print(i)
      #print(peaks[i,])
      lines(graph$V1[peaks[i,]:peaks[i+1,]], col="black")
    }
  }
 
  


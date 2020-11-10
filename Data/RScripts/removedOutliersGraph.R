setwd("E:/ECG project/ECG/Data")
outRemove <- function(x){
  graph<-read.table(paste('TXT/',x, sep=""))
  peaks<-read.table(paste('RPeaks/',x, sep=""))
  vector=c()
  for (i in 1:(length(peaks[,1])-1)){
    # print(peaks[,1][i])
    vector[i] <- (peaks[,1][i+1]-peaks[,1][i])
  }
  print(length(peaks[,1]))
  ind <- which(vector %in% boxplot.stats(vector)$out)
  if(length(ind) >0){
    print(peaks[,1][ind])
    newPeaks<-peaks[,1][-ind]
  ###########################################3  
    #write outlier peak replacement with mean value 
   ######################################### 
    #peaks[,1] <- peaks[,1][-ind]
  }
  else {
    newPeaks = peaks[,1]
  }
  print(str(newPeaks))
  print(length(newPeaks))
  j=1
  for(i in 0:2){
    print(i)
    plot(graph$V1[1:3000], type = "n")
    lines(graph$V1[(3000*i+1):(3000*(i+1))], col="black")
    while (newPeaks[j] < (i+1)*3000 & j <= length(newPeaks)) {
    #  print(peaks[,1][j])
      abline(v=newPeaks[j]-i*3000, col="red")
      j=j+1
     # print(j)
      
    }
  }
}



setwd("E:/ECG project/ECG/Data")
peakResiduals <- function(x){
  peaks<-read.table(paste('RPeaks/',x, sep=""))
  vector=c()
  for (i in 1:(length(peaks[,1])-1)){
    print(peaks[,1][i])
    vector[i] <- (peaks[,1][i+1]-peaks[,1][i])
  }
  print(vector)
 # print(length(vector))
  boxplot(vector,
          main = "peaksResiduals",
          xlab = "peaks",
          ylab = "",
          col = "green",
          border = "brown",
          horizontal = TRUE,
          notch = FALSE
  )
  ind <- which(vector %in% boxplot.stats(vector)$out)
  print(ind)

  if(length(ind) >0){
  vector=vector[-ind]}
  #print(length(vector))
  print(vector)
  print(mean(vector))
  print(median(vector))
  print(abs(mean(vector)-median(vector)))
  
}
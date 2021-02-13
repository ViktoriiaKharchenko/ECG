setwd("E:/ECG project/ECG/Data")
save <- function(x){
  graph<-read.table(paste('TXTFiltered/',x, sep=""))
  setwd("E:/ECG project/ECG/Data/CleanTXT")
  write.table(graph$V1,x)
}
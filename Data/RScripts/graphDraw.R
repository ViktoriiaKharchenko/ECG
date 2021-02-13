setwd("E:/ECG project/ECG/Data")
draw <- function(x, type,num){
types <-read.table("REFERENCE.txt")
typ<-types[num,]
print(typ)
if(typ$V2 == type){
  graph<-read.table(paste('TXTFiltered/',x, sep=""))
  peaks<-read.table(paste('RPeaks/',x, sep=""))
  j=1
  for(i in 0:2){
  ##  print(i)
    plot(graph$V1[1:3000], type = "n")
    lines(graph$V1[(3000*i+1):(3000*(i+1))], col="black")
    while (peaks[,1][j] < (i+1)*3000 & j <= length(peaks[,1])) {
      ##print(peaks[,1][j])
      abline(v=peaks[,1][j]-i*3000, col="red")
      j=j+1
     ## print(j)
      
    }
  }
}
else {
  print("Invalid type")
}

}




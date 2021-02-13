setwd("E:/ECG project/ECG/Data")
foundAF <-function(){
  types <-read.table("REFERENCE.txt")
  counter=0
  type = c()
  peaks = c()
  for(j in 1:length(types[,1])){
    print(types[j,]$V1)
    peaks[j]<-read.table(paste('RPeaks/',paste0(types[j,]$V1,".txt"), sep=""))
 # print(peaks[j])
  vector=c()
  for (i in 1:(length(peaks[[j]])-1)){
  #print(peaks[[1]][1])
    vector[i] <- (peaks[[j]][i+1]-peaks[[j]][i])
  }
  print(vector)
  # print(length(vector))
  
  print(mean(vector))
  print(median(vector))
  print(abs(mean(vector)-median(vector)))
  if(abs(mean(vector)-median(vector)) > 2.5){
    if(types[j,]$V2 == "A"){
      counter = counter +1
    }
    else{
      counter = counter -1
        }
  }
  }
  print(counter)
}
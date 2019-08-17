args <- commandArgs(TRUE)

if (length(args)==1) {
  section <- args[1]
}else{
  section <-5
}

benchmark = "dealII"
date = "FEB07"
data = read.csv(paste("AET_PIN_HIST_",benchmark,"_",date,".out",sep=""))
data1 = read.csv(paste("AET_PIN_HIST_DROP_25_",benchmark,"_",date,".out",sep=""))
data2 = read.csv(paste("AET_PIN_HIST_DROP_",benchmark,"_",date,".out",sep=""))


pdf(file=paste(benchmark,"_hist.pdf",sep=""))
barplot(data$counts,xlim=c(1,10000),names.arg = data$reuse_time, main = paste(benchmark,"_hist",sep=""),xlab ='reuse_time', ylab ='freq',log='y',offset=1)

barplot(data1$counts,xlim=c(1,10000),names.arg = data1$reuse_time, main = paste(benchmark,"_hist_D25",sep=""),xlab ='reuse_time', ylab ='freq',log='y',offset=1)

barplot(data2$counts,xlim=c(1,10000),names.arg = data2$reuse_time,main = paste(benchmark,"_hist_Drop",sep=""),xlab ='reuse_time', ylab ='freq', log='y',offset=1)

dev.off()
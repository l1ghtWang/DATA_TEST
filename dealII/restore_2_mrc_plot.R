
args <- commandArgs(TRUE)

if (length(args)==1) {
  section <- args[1]
}else{
  section <-5
}


in_file = file("inputFile.in", "r")
fileName = readLines(in_file, n = 1)
fileName1 = readLines(in_file, n = 1)
fileName2 = readLines(in_file, n = 1)
fileName3 = readLines(in_file, n = 1)
fileName4 = readLines(in_file, n = 1)
fileName5 = readLines(in_file, n = 1)
fileName6 = readLines(in_file, n = 1)
fileName7 = readLines(in_file, n = 1)
benchmark = readLines(in_file, n = 1)

data = read.csv(fileName)
data1 = read.csv(fileName1)
data2 = read.csv(fileName2)
data3 = read.csv(fileName3)
data4 = read.csv(fileName4)
data5 = read.csv(fileName5)
data6 = read.csv(fileName6)
data7 = read.csv(fileName7)

inFile1 = paste(benchmark,"_",section,"section_restored_v2_10.out", sep="")
inFile2 = paste(benchmark,"_",section,"section_restored_v2_25.out", sep="")

inFile3 = paste(benchmark,"_",section,"section_restored_v2_40.out", sep="")
inFile4 = paste(benchmark,"_",section,"section_restored_v2_50.out", sep="")

inFile5 = paste(benchmark,"_",section,"section_restored_v2_60.out", sep="")
inFile6 = paste(benchmark,"_",section,"section_restored_v2_drop.out", sep="")

inFile7 = paste(benchmark,"_",section,"section_restored_v2_90.out", sep="")


DATA1 = read.csv(inFile1)
DATA2 = read.csv(inFile2)
DATA3 = read.csv(inFile3)
DATA4 = read.csv(inFile4)
DATA5 = read.csv(inFile5)
DATA6 = read.csv(inFile6)
DATA7 = read.csv(inFile7)

pdf(file=paste(benchmark,"_",section,"section_restore_v2.pdf",sep=""))
plot(data,main = "perlbench",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data1,col=2,lty=2, pch='.')
points(data2,col=3,lty=3, pch='.')
points(data3,col=4,lty=4, pch='.')
points(data4,col=5,lty=5, pch='.')
points(data5,col=6,lty=6, pch='.')
points(data6,col=7,lty=7, pch='.')
points(data6,col=8,lty=8, pch='.')
legend(150000,0.010,legend=c("original","10","25","40","50","60","dropped","90"), col=c(1,2,3,4,5,6,7,8), pch=c(16,16,16,16,16,16,16,16), ncol=1)
 
plot(data,main = "perlbench_D10_restore_v2",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data1,col=2,lty=3, pch='.')
points(DATA1,col=3,lty=3, pch='.')
legend(150000,0.005,legend=c("original","D10","restored"), 
       col=c(1,2,3), pch=c(16,16,16), ncol=1)
 
plot(data,main = "perlbench_D25_restore_v2",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data2,col=2,lty=3, pch='.')
points(DATA2,col=3,lty=3, pch='.')
legend(150000,0.005,legend=c("original","D25","restored"), 
       col=c(1,2,3), pch=c(16,16,16), ncol=1)
 
plot(data,main = "perlbench_D40_restore_v2",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data3,col=2,lty=3, pch='.')
points(DATA3,col=3,lty=3, pch='.')
legend(150000,0.005,legend=c("original","D40","restored"), 
       col=c(1,2,3), pch=c(16,16,16), ncol=1)
 
plot(data,main = "perlbench_D50_restore_v2",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data4,col=2,lty=3, pch='.')
points(DATA4,col=3,lty=3, pch='.')
legend(150000,0.005,legend=c("original","D50","restored"), 
       col=c(1,2,3), pch=c(16,16,16), ncol=1)
 
plot(data,main = "perlbench_D60_restore_v2",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data5,col=2,lty=3, pch='.')
points(DATA6,col=3,lty=3, pch='.')
legend(150000,0.005,legend=c("original","D60","restored"), 
       col=c(1,2,3), pch=c(16,16,16), ncol=1)
 
plot(data,main = "perlbench_drop_restore_v2",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data6,col=2,lty=3, pch='.')
points(DATA6,col=3,lty=3, pch='.')
legend(150000,0.005,legend=c("original","Drop","restored"), 
       col=c(1,2,3), pch=c(16,16,16), ncol=1)
 
plot(data,main = "perlbench_D90_restore_v2",col=1,ylim = c(0,0.015),xlim = c(0,2e+05),lty=1, pch='.')
points(data7,col=2,lty=3, pch='.')
points(DATA7,col=3,lty=3, pch='.')
legend(150000,0.005,legend=c("original","D90","restored"), 
       col=c(1,2,3), pch=c(16,16,16), ncol=1)
dev.off()



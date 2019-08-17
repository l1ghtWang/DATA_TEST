
data = read.csv("AET_PIN_bzip2_AUG25.out")
data2 = read.csv("AET_PIN_DROP_25_bzip2_AUG25.out")

data3 = read.csv("AET_PIN_DROP_50_bzip2_AUG25.out")
data4 = read.csv("AET_PIN_DROP_bzip2_AUG25.out")

plot(data,main = "bzip2",ylim = c(0,0.12),xlim = c(0,80000),lty=1, pch=20)

points(data2,col="red",lty=2, pch=20)
points(data3,col="green",lty=3, pch=20)
points(data4,col="blue",lty=4, pch=20)
legend(6e+05,0.1,legend=c("original","25","50","dropped"), 
col=c("black","red","green","blue"), pch=c(0,1,2,3), ncol=1)


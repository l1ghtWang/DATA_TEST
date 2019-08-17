
data = read.csv("AET_PIN_gcc_AUG25.out")
data2 = read.csv("AET_PIN_DROP_25_gcc_AUG25.out")

data3 = read.csv("AET_PIN_DROP_50_gcc_AUG25.out")
data4 = read.csv("AET_PIN_DROP_gcc_AUG25.out")

plot(data,main = "gcc",ylim = c(0,0.15),xlim = c(0,150000),lty=1, pch=20)

points(data2,col="red",lty=2, pch=20)
points(data3,col="green",lty=3, pch=20)
points(data4,col="blue",lty=4, pch=20)
legend(4e+06,0.1,legend=c("original","25","50","dropped"), 
col=c("black","red","green","blue"), pch=c(0,1,2,3), ncol=1)




data = read.csv("AET_PIN_gamess_SEP12.out")
data2 = read.csv("AET_PIN_DROP_25_gamess_SEP12.out")

data3 = read.csv("AET_PIN_DROP_50_gamess_SEP12.out")
data4 = read.csv("AET_PIN_DROP_gamess_SEP12.out")

plot(data,main = "gamess",ylim = c(0,0.01),xlim = c(0,15000),lty=1, pch=20)

points(data2,col="red",lty=2, pch=20)
points(data3,col="green",lty=3, pch=20)
points(data4,col="blue",lty=4, pch=20)
legend(10000,0.004,legend=c("original","25","50","dropped"), 
col=c("black","red","green","blue"), pch=c(0,1,2,3), ncol=1)


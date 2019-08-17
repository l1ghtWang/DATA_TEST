data = read.csv("AET_PIN_cactusADM_AUG13.out")
data2 = read.csv("AET_PIN_DROP_25_cactusADM_AUG13.out")
data3 = read.csv("AET_PIN_DROP_50_cactusADM_AUG13.out")
data4 = read.csv("AET_PIN_DROP_cactusADM_AUG13.out")

plot(data,main = "cactusADM" #,xlim=c(0,1.4e+07)
     ,ylim = c(0, 0.03),lty=1, pch=20)

points(data2,col="red",lty=2, pch=20)
points(data3,col="green",lty=3, pch=20)
points(data4,col="blue",lty=4, pch=20)
legend(6e+06,0.03,legend=c("original","25","50","dropped"), 
col=c("black","red","green","blue"), pch=c(0,1,2,3), ncol=1)
#plot(data2,main = "GemsFDTD_25")
#plot(data3,main = "GemsFDTD_50")
#plot(data4,main = "GemsFDTD_DROP")

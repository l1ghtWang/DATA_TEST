import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 4000
my_width = 2000
my_benchmark = 'perlbench'
#date = 'FEB07'

pdf_filename = "mrc_restore_plot_"+my_benchmark+".pdf"


data = pd.read_csv('RD_MRC_TRA_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
data2 = pd.read_csv('RD_MRC_TRA_DROP_25_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
data3 = pd.read_csv('RD_MRC_TRA_DROP_50_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
data4 = pd.read_csv('RD_MRC_TRA_DROP_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)

fig1 = plt.figure()
plt.plot(data['cache_size'],data['MRC'],color='black',label='original')
plt.plot(data2['cache_size'].div(0.75),data2['MRC'],color='blue',label='D25')
plt.plot(data3['cache_size'].div(0.5),data3['MRC'],color='red',label='D50')
plt.plot(data4['cache_size'].div(1/3.5),data4['MRC'],color='green',label='drop')
plt.xlim(0,5000)
plt.legend()
plt.xlabel('cache_line')
plt.title(my_benchmark+"_MRC_restore")
#plt.show()

#plt.show()
pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.close()

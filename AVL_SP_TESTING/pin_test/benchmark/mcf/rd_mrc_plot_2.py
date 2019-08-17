import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 4000
my_width = 2000
my_benchmark = 'mcf'
#date = 'FEB07'

pdf_filename = "mrc_plot_"+my_benchmark+".pdf"


data = pd.read_csv('RD_MRC_TRA_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
data2 = pd.read_csv('RD_MRC_TRA_DROP_25_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
data3 = pd.read_csv('RD_MRC_TRA_DROP_50_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
data4 = pd.read_csv('RD_MRC_TRA_DROP_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)

fig1 = plt.figure()
plt.plot(data['cache_size'],data['MRC'],color='black',label='original')
plt.plot(data2['cache_size'],data2['MRC'],color='blue',label='D25')
plt.plot(data3['cache_size'],data3['MRC'],color='red',label='D50')
plt.plot(data4['cache_size'],data4['MRC'],color='green',label='drop')
plt.xlim(0,300000)
plt.legend()
plt.title(my_benchmark+"_MRC")
#plt.show()

#plt.show()
pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.close()
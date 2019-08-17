import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 4000
my_width = 2000
my_benchmark = 'bzip2'
#date = 'FEB07'

pdf_filename = "mrc_plot_"+my_benchmark+".pdf"


data = pd.read_csv('AVL_PIN_TRA_MRC.out',sep=',',header='infer')#,nrows=my_nrows)
data2 = pd.read_csv('AVL_PIN_TRA_MRC_DROP_25.out',sep=',',header='infer')#,nrows=my_nrows)
data3 = pd.read_csv('AVL_PIN_TRA_MRC_DROP_50.out',sep=',',header='infer')#,nrows=my_nrows)
data4 = pd.read_csv('AVL_PIN_TRA_MRC_DROP.out',sep=',',header='infer')#,nrows=my_nrows)

fig1 = plt.figure()
plt.plot(data['cache_size'],data['MRC'],color='black',label='original')
plt.plot(data2['cache_size'],data2['MRC'],color='blue',label='D25')
plt.plot(data3['cache_size'],data3['MRC'],color='red',label='D50')
plt.plot(data4['cache_size'],data4['MRC'],color='green',label='drop')
plt.xlim(0,200000)
plt.legend()
plt.title(my_benchmark+"_MRC")
#plt.show()

#plt.show()
pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.close()
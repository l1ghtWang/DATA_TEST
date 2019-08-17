#!/usr/bin/env python
# coding: utf-8

# In[1]:


import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 2000
my_width = 100
my_benchmark = 'aster'
date = 'FEB09'

pdf_filename = "hist_plot_"+my_benchmark+".pdf"
try:
	os.remove(pdf_filename) 
except FileNotFoundError:
	pass


data = pd.read_csv('AET_PIN_HIST_'+my_benchmark+'_'+date+'.out', sep=',',header='infer',nrows=my_nrows)
data2 = pd.read_csv('AET_PIN_HIST_DROP_25_'+my_benchmark+'_'+date+'.out', sep=',',header='infer',nrows=my_nrows)
data3 = pd.read_csv('AET_PIN_HIST_DROP_50_'+my_benchmark+'_'+date+'.out', sep=',',header='infer',nrows=my_nrows)
data4 = pd.read_csv('AET_PIN_HIST_DROP_'+my_benchmark+'_'+date+'.out', sep=',',header='infer',nrows=my_nrows)

for i in range(0,my_nrows-1):
	binSize = (data['reuse_time'][i+1] - data['reuse_time'][i])
	data['counts'][i] = data['counts'][i]/binSize
	data2['counts'][i] = data2['counts'][i]/binSize
	data3['counts'][i] = data3['counts'][i]/binSize
	data4['counts'][i] = data4['counts'][i]/binSize




#plt.title('Title')

fig1 = plt.figure()
#plt.semilogy(data['reuse_time'][:my_nrows-1],data['counts'])
plt.bar(data['reuse_time'][:my_nrows-1],data['counts'][:my_nrows-1],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST")
#plt.show()

# In[3]:


fig2 = plt.figure()
plt.bar(data2['reuse_time'][:my_nrows-1],data2['counts'][:my_nrows-1],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST_D25")
#plt.xlim(left=-10)
#plt.show()


# In[4]:


fig3 = plt.figure()
plt.bar(data3['reuse_time'][:my_nrows-1],data3['counts'][:my_nrows-1],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST_D50")
#plt.show()

# In[5]:
fig4 = plt.figure()
plt.bar(data4['reuse_time'][:my_nrows-1],data4['counts'][:my_nrows-1],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST_DROP")


pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.savefig( fig2 )
pdf.savefig( fig3 )
pdf.savefig( fig4 )
pdf.close()




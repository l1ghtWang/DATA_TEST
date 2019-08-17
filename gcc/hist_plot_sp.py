#!/usr/bin/env python
# coding: utf-8

# In[1]:


import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 4000
my_width = 2000
my_benchmark = 'gcc'
date = 'FEB04'

pdf_filename = "hist_plot_"+my_benchmark+"_sp.pdf"
try:
	os.remove(pdf_filename) 
except FileNotFoundError:
	pass


data = pd.read_csv('AET_PIN_HIST_'+my_benchmark+'_'+date+'.out', sep=',',header='infer',nrows=my_nrows)
data1 = pd.read_csv('AET_PIN_HIST_DROP_25_'+my_benchmark+'_SP.out', sep=',',header='infer',nrows=my_nrows)
data2 = pd.read_csv('AET_PIN_HIST_DROP_50_'+my_benchmark+'_SP.out', sep=',',header='infer',nrows=my_nrows)
data3 = pd.read_csv('AET_PIN_HIST_DROP_'+my_benchmark+'_SP.out', sep=',',header='infer',nrows=my_nrows)

#x = [i for i in range(data['counts'].size)]
#data.plot(x='reuse_time', y='counts', kind='scatter')
#plt.ylabel('Frequency')
#plt.xlabel('Words')


# In[2]:


#plt.title('Title')

fig1 = plt.figure()
#plt.semilogy(data['reuse_time'],data['counts'])
plt.bar(data['reuse_time'],data['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST")
plt.show()

# In[3]:


fig2 = plt.figure()
plt.bar(data1['reuse_time'],data1['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST_D25_SP")
#plt.xlim(left=-10)
plt.show()


# In[4]:


fig3 = plt.figure()
plt.bar(data2['reuse_time'],data2['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST_D50_SP")
plt.show()

# In[5]:



fig4 = plt.figure()
plt.bar(data2['reuse_time'],data2['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_HIST_DROP_SP")
plt.show()


pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.savefig( fig2 )
pdf.savefig( fig3 )
pdf.savefig( fig4 )
pdf.close()




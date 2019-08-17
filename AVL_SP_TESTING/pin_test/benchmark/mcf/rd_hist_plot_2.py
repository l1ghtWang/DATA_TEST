import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 8000
my_width = 2000
my_benchmark = 'mcf'
#date = 'FEB07'

pdf_filename = "hist_plot_"+my_benchmark+".pdf"

data = pd.read_csv('RD_HIST_TRA_'+my_benchmark+'.out',sep=',',header='infer',nrows=my_nrows)
data2 = pd.read_csv('RD_HIST_TRA_DROP_25_'+my_benchmark+'.out',sep=',',header='infer',nrows=my_nrows)
data3 = pd.read_csv('RD_HIST_TRA_DROP_50_'+my_benchmark+'.out',sep=',',header='infer',nrows=my_nrows)
data4 = pd.read_csv('RD_HIST_TRA_DROP_'+my_benchmark+'.out',sep=',',header='infer',nrows=my_nrows)


fig1 = plt.figure()
plt.bar(data['reuse_distance'],data['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.ylim(1,10**10)
plt.title(my_benchmark+"_hist")
#plt.show()

fig2 = plt.figure()
plt.bar(data2['reuse_distance'],data2['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.ylim(1,10**10)
plt.title(my_benchmark+"_hist_D25")

fig3 = plt.figure()
plt.bar(data3['reuse_distance'],data3['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.ylim(1,10**10)
plt.title(my_benchmark+"_hist_D50")

fig4 = plt.figure()
plt.bar(data4['reuse_distance'],data4['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.ylim(1,10**10)
plt.title(my_benchmark+"_hist_DROP")

pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.savefig( fig2 )
pdf.savefig( fig3 )
pdf.savefig( fig4 )
pdf.close()
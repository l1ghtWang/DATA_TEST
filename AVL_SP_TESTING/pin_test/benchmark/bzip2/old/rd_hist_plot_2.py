import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 1000
my_width = 500
my_benchmark = 'bzip2'
#date = 'FEB07'

pdf_filename = "hist_plot_"+my_benchmark+".pdf"

data = pd.read_csv('AVL_PIN_TRA_HIST.out',sep=',',header='infer',nrows=my_nrows)
data2 = pd.read_csv('AVL_PIN_TRA_HIST_DROP_25.out',sep=',',header='infer',nrows=my_nrows)
data3 = pd.read_csv('AVL_PIN_TRA_HIST_DROP_50.out',sep=',',header='infer',nrows=my_nrows)
data4 = pd.read_csv('AVL_PIN_TRA_HIST_DROP.out',sep=',',header='infer',nrows=my_nrows)


fig1 = plt.figure()
plt.bar(data['reuse_distance'],data['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_hist")
#plt.show()

fig2 = plt.figure()
plt.bar(data2['reuse_distance'],data2['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_hist_D25")

fig3 = plt.figure()
plt.bar(data3['reuse_distance'],data3['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_hist_D50")

fig4 = plt.figure()
plt.bar(data4['reuse_distance'],data4['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_hist_DROP")

pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.savefig( fig2 )
pdf.savefig( fig3 )
pdf.savefig( fig4 )
pdf.close()
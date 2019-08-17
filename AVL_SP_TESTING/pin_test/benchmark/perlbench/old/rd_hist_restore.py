import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 1000
my_width = 500
my_benchmark = 'perlbench'
#date = 'FEB07'

pdf_filename = "restore_hist_plot_"+my_benchmark+".pdf"

data = pd.read_csv('AVL_PIN_TRA_HIST.out',sep=',',header='infer',nrows=my_nrows)
data2 = pd.read_csv('AVL_PIN_TRA_HIST_DROP_25.out',sep=',',header='infer',nrows=my_nrows)
data3 = pd.read_csv('AVL_PIN_TRA_HIST_DROP_50.out',sep=',',header='infer',nrows=my_nrows)
data4 = pd.read_csv('AVL_PIN_TRA_HIST_DROP.out',sep=',',header='infer',nrows=my_nrows)

newData2 = [ i/(1-0.25) for i in data2['reuse_distance']]
newData3 = [ i/(1-0.50) for i in data3['reuse_distance']]
newData4 = [ i/(2.0/7.0) for i in data4['reuse_distance']]




fig1 = plt.figure()
plt.bar(data['reuse_distance'],data['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title("restore_"+my_benchmark+"_hist")
#plt.show()

fig2 = plt.figure()
plt.bar(newData2,data2['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title("restore_"+my_benchmark+"_hist_D25")

fig3 = plt.figure()
plt.bar(newData3,data3['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title("restore_"+my_benchmark+"_hist_D50")

fig4 = plt.figure()
plt.bar(newData4,data4['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title("restore_"+my_benchmark+"_hist_DROP")

pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.savefig( fig2 )
pdf.savefig( fig3 )
pdf.savefig( fig4 )
pdf.close()
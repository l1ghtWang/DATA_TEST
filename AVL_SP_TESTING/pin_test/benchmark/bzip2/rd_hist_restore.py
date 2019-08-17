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

mrc = pd.read_csv('RD_MRC_TRA_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
hist2 = pd.read_csv('RD_HIST_TRA_DROP_25_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
hist3 = pd.read_csv('RD_HIST_TRA_DROP_50_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)
hist4 = pd.read_csv('RD_HIST_TRA_DROP_'+my_benchmark+'.out',sep=',',header='infer')#,nrows=my_nrows)

restoreHist2 = [ i/(1-0.25) for i in hist2['reuse_distance']]
restoreHist3 = [ i/(1-0.50) for i in hist3['reuse_distance']]
restoreHist4 = [ i/(2.0/7.0) for i in hist4['reuse_distance']]




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
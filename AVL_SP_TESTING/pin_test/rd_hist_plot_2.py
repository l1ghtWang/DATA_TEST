import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 20000
my_width = 2000
my_benchmark = 'msr_proj'
date = 'FEB07'

pdf_filename = "hist_msr_proj_2.pdf"
data = pd.read_csv('test2.hist',sep=',',header='infer',nrows=my_nrows)
fig1 = plt.figure()
plt.bar(data['reuse_dist'],data['counts'],width=my_width,color='b',align='edge')
plt.yscale("log")
plt.title(my_benchmark+"_hist")
#plt.show()

pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.close()
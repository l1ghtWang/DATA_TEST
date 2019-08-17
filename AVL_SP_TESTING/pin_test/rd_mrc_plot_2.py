import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import matplotlib.backends.backend_pdf
import os

my_nrows = 4000
my_width = 2000
my_benchmark = 'msr_proj'
date = 'FEB07'

pdf_filename = "mrc_msr_proj_2.pdf"
data = pd.read_csv('test2.mrc')
fig1 = plt.figure()
#plt.semilogy(data['reuse_time'],data['counts'])
plt.plot(data['cache_size'],data['mrc'],color='b')
#plt.yscale("log")
plt.title(my_benchmark+"_MRC")
#plt.show()

pdf = matplotlib.backends.backend_pdf.PdfPages(pdf_filename)
pdf.savefig( fig1 )
pdf.close()
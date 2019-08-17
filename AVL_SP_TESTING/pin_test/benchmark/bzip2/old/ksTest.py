import scipy.stats as ss
import numpy as np
import pandas as pd
import matplotlib.backends.backend_pdf
import os

data = pd.read_csv('test.out', sep=',',header=None)#,nrows=my_nrows)

print(ss.kstest(data[0],ss.uniform(loc=0.0, scale=4294967296.0).cdf))

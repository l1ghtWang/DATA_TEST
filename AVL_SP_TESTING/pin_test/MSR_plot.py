import matplotlib.pyplot as plt
import numpy as np
width = 10
height = 8
lw = 1.2


plt.gcf().set_size_inches(width, height)
plt.title("msr_src1_0.hist", loc='center')

plt.ylabel('count')
plt.xlabel('Cache size (obj)')

fig, axs = plt.subplots(1, 2, sharey=True, tight_layout=True)

names = ['1.0000','0.0010']
colors = ['b', 'g', 'r', 'c']
for i in range(len(names)):
    xs = []
    ys = []
    with open('src1_0.csv_lru.R'+names[i]+'.hist') as f:
        f.readline()
        f.readline()
        for line in f:
            z = [float(x.strip()) for x in line.split(',')]
            xs.append(z[0])
            ys.append(z[1])
        y_pos = np.arange(len(xs))
    axs[i].bar(y_pos, ys, align='center', alpha=0.5)


plt.savefig('msr_mds_0_hist.png')
names = ['1.0000', '0.1000', '0.0100', '0.0010']
colors = ['b', 'g', 'r', 'c']
for i in range(len(names)):
    xs = []
    ys = []
    with open('src1_0.csv_lru.R'+names[i]+'.mrc') as f:
        for line in f:
            z = [float(x.strip()) for x in line.split(',')]
            xs.append(z[0])
            ys.append(z[1])

    ys = [i*100 for i in ys]
    plt.plot(xs, ys, colors[i], label='R = '+names[i], linewidth=lw)


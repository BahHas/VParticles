
from matplotlib.colors import LogNorm
import numpy as np
import matplotlib.pyplot as plt
import  math
import glob


munuc = []
colum = []
ion = []
decay = []
with open("test.txt","r") as fi:
    for ln in fi:
        if ln.startswith("MMMMMMMMM:"):
            munuc.append(float(ln[10:]))
        elif ln.startswith("CCCCCCCCC:"):
            if float(ln[10:]) < 1e20:
                colum.append(float(ln[10:]))
        elif ln.startswith("IIIIIIIII:"):
            if float(ln[10:]) < 1e20:
                ion.append(float(ln[10:]))
        elif ln.startswith("DDDDDDDDD:"):
            decay.append(float(ln[10:]))




print (sum(munuc) / len(munuc), sum(colum) / len(colum), sum(ion) / len(ion), sum(decay) / len(decay))
plt.hist(ion)
#plt.xlim(0, 1e10)
#plt.xscale('log')
plt.yscale('log')
plt.show()

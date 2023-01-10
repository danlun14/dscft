import os
import time

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker

def main():
    datafiles = ["results/NFDH_1152N.txt", "results/FFDH_1152N.txt"]
    labels = ["NFDH", "FFDH"]
    cm = 1/2.54  # centimeters in inche
    fig = plt.figure(figsize=(16*cm, 10*cm))
    ax = fig.add_subplot(111)
    colors=["blue", "red"]

    ax.set(xlabel="Count tasks", ylabel="Alg time (sec)", title="График зависимости времени выполнения алгоритмов от числа задач")
    for i in range(len(datafiles)):
        data = np.loadtxt(datafiles[i], skiprows=1)
        x = data[:, 0]
        y = data[:, 4]
        ax.plot(x,y,'o-',markersize=2,c=colors[i],label=labels[i])
        ax.legend();
    fig.savefig('Alg_time.png', dpi=300)

    ax.clear()
    ax.set(xlabel="Count tasks", ylabel="Packing time (sec)", title="График зависимости эффективности упаковки от числа задач")
    for i in range(len(datafiles)):
        data = np.loadtxt(datafiles[i], skiprows=1)
        x = data[:, 0]
        y = data[:, 1]
        ax.plot(x,y,'o-',markersize=2,c=colors[i],label=labels[i])
        ax.legend();
    fig.savefig('Packaging efficiency.png', dpi=300)
    return 0

if __name__ == "__main__":
	main()
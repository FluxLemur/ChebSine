import numpy as np
import matplotlib.pyplot as plt

x, y = np.loadtxt("err.dat", unpack=True, skiprows=1)

f = open("err.dat")

plt.title(f.readline())
plt.xlabel("x values")
plt.ylabel("error from machine sine")
plt.plot(x, y)
plt.show()

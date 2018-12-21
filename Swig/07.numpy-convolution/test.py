import convolution as stm
import numpy as np

a = np.linspace(0, 1, 20)
print (a.shape)
a = a.reshape((a.shape[0], 1))
print (a.shape)
print(a)
c = stm.convolve2d(a, 1)
print (c)

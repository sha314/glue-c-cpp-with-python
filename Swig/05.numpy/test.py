import carray as my_mod
import numpy as np


a = my_mod.range(10)
print(a)

a = np.linspace(0, 1, 10)
b = my_mod.twice(a)
print(b)
print(a)

a = my_mod.dot(np.ones(10),np.ones(10)*2)
print(a)

my_mod.view_vector([1.0,2.0,3.0,4.0,100.0])

a = np.arange(0, 10, 1)
b = my_mod.foo(a)
print(b)
print(b*2)

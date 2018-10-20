import myextension
import numpy as np


a = myextension.copy_and_sum([1,2,3])
print(a)

a = myextension.sum_list([1,2,3])
print(a)

# a = myextension.add_two_list([1,2,3], [3,2,1])
# print(a)

# x = np.array([1,2,3,4])
# a = myextension.view_numpy_array(x)
# print(a)
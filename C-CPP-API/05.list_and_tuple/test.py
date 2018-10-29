import myextension
import numpy as np

print('view----------------------------------------------------')
a = myextension.view([1,2,3])
print(a)

print('sum-----------------------------------------------------')
a = myextension.sum_list([1,2,3])
print(a)

print('copy and sum---------------------------------------------')
a = myextension.copy_and_sum([1,2,3])
print(a)

print('copy and squared sum-------------------------------------')
a = myextension.copy_and_squared_sum([1,2,3])
print(a)

print('copy and sum two list using keyword argument--------------')
a = myextension.copy_and_sum_two_list_by_keyword_args(a=[1,2,3], b=[3,2,1])
print(a)

print('copy and sum tuple----------------------------------------')
tpl = (1,2,3)
a = myextension.tuple_sum(tpl)
print(a)


print('copy and square tuple----------------------------------------')
tpl = (1,2,3)
a = myextension.round_trip(tpl)
print(a)

# x = np.array([1,2,3,4])
# a = myextension.view_numpy_array(x)
# print(a)
import myextension
import numpy as np

print('view-1D-------------------------------------------------')
a = myextension.view([1,2,3])
print(a)
print('view-2D-------------------------------------------------')
a = myextension.view([[1, 10],
					  [2, 20],
					  [3, 30]])
print(a)
print('view-3D-------------------------------------------------')
a = myextension.view([[[1, -10], [10]],
					  [[2, -20], [20]],
					  [[3, -30], [30]]])
print(a)

print('view_matrix-----------------------------------------------------')
a = np.random.randint(0, 10, 9)
# print(a)
a = a.reshape((3,3))
print('python')
print(a)
a = myextension.view_matrix(a.tolist())
print(a)

print('round_trip------------------------------------------------------')
a = np.random.randint(0, 10, 9)
# print(a)
a = a.reshape((3,3))
print('python')
print(a)
a = myextension.round_trip(a.tolist())
print(a)


print('matrix multiplication---------------------------------------------')
a = np.random.randint(0, 10, 9)
# print(a)
a = a.reshape((3,3))
b = [
	[1, 0, 0],
	[0, 1, 0],
	[0, 0, 1]
		]
print('python')
print(a)
print(np.array(b))
c = myextension.mat_mul(a=a.tolist(), b=b)
print(np.array(c))
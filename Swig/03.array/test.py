import carray as my_mod

a = my_mod.ones(10)
print(a)

x = [1.0,2.0,3.0]
w = my_mod.sum(x)
print(w)

print("testing matrix multiplication--------------")
print("passed by value")
a = [
	[1.0, 2.0, 3.0],
	[3.0, 2.0, 1.5],
	[1.0, 1.5, 2.5]
]

i = [
	[1.0, 0.0, 0.0],
	[0.0, 1.0, 0.0],
	[0.0, 0.0, 1.0]
]

m = my_mod.matrix_mul(a, i)
print(m)
my_mod.view(m)
 
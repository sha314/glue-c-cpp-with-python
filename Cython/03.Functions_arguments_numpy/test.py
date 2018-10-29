print("importing...")
# from helloextension import c_hello
# from helloextension import c_factorial
import functionextension
import numpy as np

def main():
	print("testing cython")
	x = [10,-2,35]
	functionextension.py_view_array(x)
	y = [[1,2], [30,40], [5, 6, 7]]
	functionextension.py_view_array_2d(y)
	z = np.array(y)
	print(z.shape)
	functionextension.py_view_array_2d(z)
	x2 = functionextension.py_add(np.ones(10), np.ones(10))
	print("type of the returened result : ", type(x2))
	print(x2)

	A = np.array(
		[[1, 0, 0],
	 	 [0, 1, 0],
	 	 [0, 0, 1]])

	B = np.array(
		[[1.2, 2.3, 3.4],
	 	 [0, 11, 5],
	 	 [0, -10, 1]])

	C = functionextension.py_mat_mul(A, B)
	print(C)

if __name__ == "__main__":
	main()

    
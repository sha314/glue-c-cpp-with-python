print("importing...")
# from helloextension import c_hello
# from helloextension import c_factorial
import functionextension


def main():
    print("testing cython")
    x = functionextension.py_factorial(4)
    print(x)
    x = [10,-2,35]
    functionextension.py_view_array(x)
    y = [[1,2], [30,40], [5, 6, 7]]
    functionextension.py_view_array_2d(y)


if __name__ == "__main__":
    main()

    
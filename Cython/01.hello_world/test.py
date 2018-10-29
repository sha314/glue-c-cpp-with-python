print("importing...")
# from helloextension import c_hello
# from helloextension import c_factorial
import helloextension


def main():
    print("testing cython")
    helloextension.py_hello()
    x = helloextension.py_factorial(4)
    print(x)


if __name__ == "__main__":
    main()

    
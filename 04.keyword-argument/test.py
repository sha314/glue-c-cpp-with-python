import myextension

print("keywork argument demostration")
print("one argument")
x = myextension.one_keyword_argument(n=10)
print(x)

print("two argument")
y = myextension.mandatory_keyword_argument_add(a=2,b=3)
print(y)

print('two argument, one default, one prvided')
z = myextension.optional_keyword_argument_add(a=2)
print(z)
print('two argument, one default, two prvided')
z = myextension.optional_keyword_argument_add(a=2,b=10)
print(z)
print('two argument, one default, different order')
z = myextension.optional_keyword_argument_add(b=10,a=2)
print(z)

print("two argument, one default, type is PyObject")
z = myextension.optional_keyword_argument_py_object(a=3, b=4);
print(z)
# print(help(myextension.optional_keyword_argument_add))



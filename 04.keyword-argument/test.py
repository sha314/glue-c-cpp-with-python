import myextension

print("keywork argument demostration")
x = myextension.one_keyword_argument(n=10)
print(x)

y = myextension.mandatory_keyword_argument_add(a=2,b=3)
print(y)

z = myextension.optional_keyword_argument_add(a=2)
print(z)

z = myextension.optional_keyword_argument_add(a=2,b=10)
print(z)

# print(help(myextension.optional_keyword_argument_add))



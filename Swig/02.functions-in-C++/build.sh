# build.sh

# generating wrapping source files
echo generating wrapping source files ..............
swig -python -c++ cppfunc.i

# compiling
echo compiling......................................
g++ -fPIC -c src/example.cpp cppfunc_wrap.cxx -I/usr/include/python3.6m/

# or
#-I/home/shahnoor/software/anaconda3/include/python3.7m/

# linking
echo linking .........................................
g++ -shared example.o cppfunc_wrap.o -o _cppfunc.so -lstdc++


echo removing redundant files.........................
rm *_wrap*
rm *.o

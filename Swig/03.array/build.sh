# build.sh

# generating wrapping source files
echo generating wrapping source files ..............
swig -python -c++ carray.i

# compiling
echo compiling......................................
g++ -fPIC -c -std=c++11 src/myarray.cpp carray_wrap.cxx -I/usr/include/python3.6m/

# or
#-I/home/shahnoor/software/anaconda3/include/python3.7m/

# linking
echo linking .........................................
g++ -shared  myarray.o carray_wrap.o -o _carray.so -lstdc++


echo removing redundant files.........................
#rm *_wrap*
#rm *.o

# build.sh

# generating wrapping source files
echo generating wrapping source files ..............
swig -python -c++ convolution.i

# compiling
echo compiling......................................
# g++ -fPIC -c -std=c++11 convolution.cpp convolution_wrap.cxx  -I/usr/include/python3.6m -I/home/shahnoor/.local/lib/python3.6/site-packages/numpy/core/include/
g++ -fPIC -c -std=c++11 -fopenmp convolution.cpp convolution_wrap.cxx  -I/usr/include/python3.6m -I/home/shahnoor/.local/lib/python3.6/site-packages/numpy/core/include/

# or
#-I/home/shahnoor/software/anaconda3/include/python3.7m/

# linking
echo linking .........................................
g++ -fopenmp -shared  convolution.o convolution_wrap.o -o _convolution.so -lstdc++


echo removing redundant files.........................
rm *_wrap*
rm *.o

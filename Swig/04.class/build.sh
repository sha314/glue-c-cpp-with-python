# build.sh

# generating wrapping source files
echo generating wrapping source files ..............
swig -python -c++ word.i

# compiling
echo compiling......................................
g++ -fPIC -c src/word.cpp word_wrap.cxx -I/usr/include/python3.6m/

# or
#-I/home/shahnoor/software/anaconda3/include/python3.7m/

# linking
echo linking .........................................
g++ -shared word.o word_wrap.o -o _word.so -lstdc++


echo removing redundant files.........................
rm *_wrap*
rm *.o

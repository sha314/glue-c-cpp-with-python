# build.sh

# generating wrapping source files
echo generating wrapping source files ..............
swig -python example.i

# compiling
echo compiling......................................
gcc -fPIC -c src/example.c example_wrap.c -I/usr/include/python3.6m/

# or
#-I/home/shahnoor/software/anaconda3/include/python3.7m/

# linking
echo linking .........................................
gcc -shared example.o example_wrap.o -o _example.so 

echo cleaning..........................................
rm *.o
rm *_wrap.c
echo removing example.py file will result in ModuleNotFoundError
#rm example.py
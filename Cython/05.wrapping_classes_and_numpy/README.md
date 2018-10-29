1. function with std::vector argument. One dimensional. done
2. function with std::vector argument. Two dimensional. done
3. function with std::vector argument with numpy. One dimensional 
4. function with std::vector argument with numpy. Two dimensional 



```
Error warning:
	To prevent:
		fatal error: numpy/arrayobject.h: No such file or directory
 		#include "numpy/arrayobject.h"
 	Use:
		In your setup.py, the Extension should have the argument include_dirs=[numpy.get_include()].

```

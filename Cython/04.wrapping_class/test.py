# Python running example

from __future__ import print_function

import numpy as np
from rectangleExtension import PyRectangle

# Initialising the wrapped c++ function
R1 = PyRectangle(0, 1, 9, 9);

#Test1: Doing the area example calculation
print("length: ", R1.getLength())
print("height: ", R1.getHeight())
print("Area: ", R1.getArea())
print("move: ", R1.move(1, 2))
print("length: ", R1.getLength())
print("height: ", R1.getHeight())
print("Area: ", R1.getArea())


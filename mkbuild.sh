#!/bin/bash
clear
# g++ -o pc main.cpp math_operators.cpp
# stack.cpp
g++ -O3 -o pc $(ls *.cpp)
if [ "$?" == "0" ]; then
	./pc $@
fi

#!/bin/bash
cd src
doxygen ../doc/Doxyfile > /dev/null
gcc -g graf.c generic_tree.c generic_queue.c generic_linkedlist.c io.c algorithms.c -o ../bin/graf.out
cd ..
valgrind --leak-check=full bin/graf.out -v dat/csucsok.dat -e dat/elek.dat -d 1

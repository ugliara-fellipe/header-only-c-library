# Header-Only C Library

This project is a C header-only library. The development respects the 
following definitions:

- use only C header files to avoid preview compilations
- implement facilities not find in C, like objects and exceptions
- keep the library use simple, not the implementation simple
- use C17 standard library only

# How to Use

Only copy the header files (.h) in your project and include them in the 
code. The tests are good examples of it. If you need some compiler 
explanations look the Makefile, the script to compiler tests are in this
file.

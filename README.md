# STL helper functions library

STL helper functions code library project is a small, simple cross-platform modern C++ code library, 
which at the moment consists of only one C++ header file (stl_helper_functions.hpp). 
The code library contains some useful macros, metafunctions, type functions, structs, enums, 
various function templates and generic algorithms, which can be used in an existing code base 
to make interfacing with various components of the STL C++ library somewhat easier, friendlier 
and more approachable.

To use this code library you simply need to add stl_helper_functions.hpp to your project 
and include it into your source code file(s). 

All the implemented metafunctions, type functions, structs, enums and function templates are defined 
in the stl::helper namespace. Make sure to use a modern C++ compiler (one that is fully compliant 
with the c++17 language standard or a newer one such as c++2a) in order to compile your project 
which makes use of this code library.

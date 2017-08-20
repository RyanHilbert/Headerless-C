# Macros
The headerless.h file defines several macros that allow .c sources to be included directly, removing the need for accompanying header files!
## H
The H macro (header) affects most other macros in headerless.h. H enables "header mode" when defined, causing most other macros to expand more conservatively. This should be defined before #include-ing a "headerless" .c file.
### Usage
	#define H
	#include "file.c"
## B
The B macro (body) is used to define function bodies in headerless .c files.
### Usage
	unsigned factorial(unsigned i)B(
		unsigned n = 1;
		while(i) n *= i--;
		return n;
	)
## C
The C macro (extern"C") can be used to specify C linkage, in case a headerless .c file is included by a C++ file.
### Usage
	C double sq(double x)B(
		return x*x;
	)
## E
The E macro (equals) is used to initialize non-static variables in headerless .c files.
### Usage
	int value E(0)
## S
The S macro (static) is used to define static functions and variables in headerless .c files.
### Usage
	S(int value=0)
	S(double sq(double x))B(
		return x*x;
	)

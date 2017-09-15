# Macros
The headerless.h file defines several macros that allow .c sources to be included directly, removing the need for accompanying header files.
## H
The H macro (header) affects most other macros in headerless.h. H enables "header mode" when defined, causing most other macros to expand more conservatively. This should be defined before #include-ing a "headerless" .c file.

	#define H
	#include "file1.c"
	#include "file2.c"
## B
The B macro (body) is used to define function bodies in headerless .c files.

	unsigned factorial(unsigned i)B(
		unsigned n = 1;
		while(i) n *= i--;
		return n;
	)
## C
The C macro (extern"C") can be used to specify C linkage, in case a headerless .c file is included by a C++ file.

	C double sq(double x)B(
		return x*x;
	)
## E
The E macro (equals) is used to initialize non-static variables in headerless .c files.

	int value E(0)
## S
The S macro (static) is used to define static functions and variables in headerless .c files.

	S(int value=0;)
	S(double sq(double x))B(
		return x*x;
	)
# Usage
Including a headerless .c file in a normal file is fairly straightforward, as shown in the H macro example. However, complications arise when a headerless file tries to include other headerless files. For instance, assume we want to create our own headerless file.c which includes other headerless .c files, file1.c and file2.c:

	#define H // WRONG - Now we can't use H to detect whether this file is being compiled or included!
	#include "file1.c"
	#include "file2.c"
	#include "headerless.h"
	//code...
A potential way to resolve this might be:

	#ifdef H
	#include "file1.c"
	#include "file2.c"
	#else
	#define H
	#include "file1.c"
	#include "file2.c"
	#undef H
	#endif
	#include "headerless.h"
	//code...
However, this is quite verbose and requires listing all our .c includes twice. To prevent the duplication, we can do this:

	#ifdef FILE_C
	#include "file1.c"
	#include "file2.c"
	#else
	#define FILE_C
	
	#ifdef H
	#include __FILE__
	#else
	#define H
	#include __FILE__
	#undef H
	#endif
	
	#include "headerless.h"
	//code...
	#endif
But this is still quite verbose! Fortunately, "headerless.h" allows F to be defined as the name of a file; if it is, the header will perform this inclusion for us:

	#ifdef FILE_C
	#include "file1.c"
	#include "file2.c"
	#else
	#define FILE_C
	
	#define F "file.c"
	#include "headerless.h"
	//code...
	#endif
Finally, to deal with multiple or recursive inclusion, we still need an include guard:

	#if FILE_C
	#undef FILE_C
	#define FILE_C
	#include "file1.c"
	#include "file2.c"
	#elif !defined(FILE_C)
	#define FILE_C 1
	
	#define F "file.c"
	#include "headerless.h"
	//code...
	#endif
Putting everything together gives us the working example above, allowing removal of header files at the cost of a minimal amount of boilerplate.

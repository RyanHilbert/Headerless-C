#ifdef F
#ifdef H
#include F
#else
#define H
#include F
#undef H
#endif
#undef F
#endif

#undef B
#ifdef H
#define B(...);
#else
#define B(...){__VA_ARGS__}
#endif

#undef C
#ifdef __cplusplus
#define C extern"C"
#else
#define C
#endif

#undef E
#ifdef H
#define E(...);
#else
#define E(...)=__VA_ARGS__;
#endif

#undef S
#ifdef H
#define S(...)
#else
#define S(...)static __VA_ARGS__;
#endif

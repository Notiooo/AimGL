#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <stdlib.h>

#if defined(_DEBUG)
// #undef MTR_ENABLED// Comment to enable MiniTrace
#endif


constexpr static auto IS_MINITRACE_COLLECTING_AT_START = false;
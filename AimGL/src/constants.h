#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <stdlib.h>

#ifndef _DEBUG
    #undef MTR_ENABLED
#endif

constexpr static auto IS_MINITRACE_COLLECTING_AT_START = false;
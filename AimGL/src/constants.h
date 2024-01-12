#pragma once

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <stdlib.h>

#ifndef _DEBUG
    #undef MTR_ENABLED
#endif

constexpr static auto IS_MINITRACE_COLLECTING_AT_START = false;

// Not a good idea. But run out of time :P
#ifdef _DEBUG
extern bool DRAW_COLLIDERS;
#else
constexpr static auto DRAW_COLLIDERS = false;
#endif
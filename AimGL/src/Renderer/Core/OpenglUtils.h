#pragma once

/**
 * Activates breakpoint
 */
#ifdef _MSC_VER
    #define ASSERT(x)                                                                              \
        if (!x)                                                                                    \
            __debugbreak();
#else
    #define ASSERT(x)                                                                              \
        if (!x)                                                                                    \
            raise(SIGTRAP);
#endif

/**
 * Macro to use on OpenGL functions to correctly catch errors and write them out
 */
#define GLCall(x)                                                                                  \
    GLClearError();                                                                                \
    x;                                                                                             \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__));

/**
 * Cleans up OpenGL errors
 */
void GLClearError();

/**
 * Prints an error if an OpenGL error occurred
 * @param function The function in which the error occurred
 * @param file The name of the file in which the error occurred
 * @param line The line where the error occurred
 * @return False if the error occurred, true otherwise
 */
bool GLLogCall(const char* function, const char* file, int line);
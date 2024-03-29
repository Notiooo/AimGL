#include "Renderer/Core/OpenglUtils.h"
#include "pch.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {
        ;
    }
}

bool GLLogCall(const char* function, const char* file, int line)
{
    if (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (0x" << std::hex << error << std::dec << "): " << function
                  << " " << file << " at line: " << line << std::endl;
        return false;
    }
    return true;
}
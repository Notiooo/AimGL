#include "Renderer/Core/Shader.h"

#include "Renderer/Core/OpenglUtils.h"
#include "pch.h"
#include <fstream>


Shader::Shader(std::initializer_list<ShaderSource> shaders)
    : mRendererId(0)
{
    auto parsedShaders = parseShaders(shaders);
    mRendererId = createShader(parsedShaders);
    GLCall(glUseProgram(mRendererId));
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(mRendererId));
}

void Shader::bind() const
{
    GLCall(glUseProgram(mRendererId));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform(const std::string& name, glm::mat4 mat) const
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat[0])));
}

void Shader::setUniform(const std::string& name, glm::vec4 vec) const
{
    GLCall(glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(vec)));
}

void Shader::setUniform(const std::string& name, glm::vec3 vec) const
{
    GLCall(glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(vec)));
}

void Shader::setUniform(const std::string& name, float f1, float f2, float f3, float f4) const
{
    GLCall(glUniform4f(getUniformLocation(name), f1, f2, f3, f4));
}

void Shader::setUniform(const std::string& name, float f1, float f2, float f3) const
{
    GLCall(glUniform3f(getUniformLocation(name), f1, f2, f3));
}

void Shader::setUniform(const std::string& name, float f1, float f2) const
{
    GLCall(glUniform2f(getUniformLocation(name), f1, f2));
}

void Shader::setUniform(const std::string& name, float f1) const
{
    GLCall(glUniform1f(getUniformLocation(name), f1));
}

void Shader::setUniform(const std::string& name, int i1, int i2, int i3, int i4) const
{
    GLCall(glUniform4i(getUniformLocation(name), i1, i2, i3, i4));
}

void Shader::setUniform(const std::string& name, int i1, int i2, int i3) const
{
    GLCall(glUniform3i(getUniformLocation(name), i1, i2, i3));
}

void Shader::setUniform(const std::string& name, int i1, int i2) const
{
    GLCall(glUniform2i(getUniformLocation(name), i1, i2));
}

void Shader::setUniform(const std::string& name, int i1) const
{
    GLCall(glUniform1i(getUniformLocation(name), i1));
}

unsigned Shader::getUniformLocation(const std::string& name) const
{
    if (mUniformLocationCache.find(name) != mUniformLocationCache.end())
    {
        return mUniformLocationCache[name];
    }

    GLCall(auto location = glGetUniformLocation(mRendererId, name.c_str()));
    if (location == -1)
    {
        spdlog::warn("No uniform with name {} exist", name);
    }

    mUniformLocationCache[name] = location;

    return location;
}

std::vector<Shader::ShaderSourceCode> Shader::parseShaders(const std::vector<ShaderSource>& shaders)
{
    std::vector<Shader::ShaderSourceCode> shaderSourceCode;
    for (const auto& shader: shaders)
    {
        std::ifstream sourceFile(shader.filePath, std::fstream::in);
        std::string sourceCode;
        if (sourceFile.is_open())
        {
            sourceCode = std::string(std::istreambuf_iterator<char>(sourceFile),
                                     std::istreambuf_iterator<char>());

            shaderSourceCode.push_back(ShaderSourceCode{shader, sourceCode});
        }
    }
    return shaderSourceCode;
}

std::vector<unsigned> Shader::compileShaders(const std::vector<Shader::ShaderSourceCode>& shaders)
{
    std::vector<unsigned> compiledShaders;
    compiledShaders.reserve(shaders.size());
    for (const auto& shader: shaders)
    {
        compiledShaders.emplace_back(compileShader(shader));
    }
    return compiledShaders;
}

void Shader::attachShaders(unsigned program, const std::vector<unsigned>& compiledShaders)
{
    for (const auto& compiledShader: compiledShaders)
    {
        GLCall(glAttachShader(program, compiledShader));
    }
}

void Shader::logInCaseOfIncorrectlyLinkedProgram(unsigned program)
{
    auto isProgramLinkedCorrectly = 0;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &isProgramLinkedCorrectly));
    if (not isProgramLinkedCorrectly)
    {
        auto logLength = 0;
        char message[1024];
        GLCall(glGetProgramInfoLog(program, 1024, &logLength, message));
        spdlog::error("Failed to link shader program. Opengl error message:\n {}", message);
    }
}

void Shader::deleteShaders(const std::vector<unsigned>& compiledShaders)
{
    for (const auto& compiledShader: compiledShaders)
    {
        GLCall(glDeleteShader(compiledShader));
    }
}

unsigned Shader::createShader(const std::vector<Shader::ShaderSourceCode>& shaders)
{
    auto program = static_cast<unsigned int>(glCreateProgram());
    auto compiledShaders = compileShaders(shaders);
    attachShaders(program, compiledShaders);
    GLCall(glLinkProgram(program));
    logInCaseOfIncorrectlyLinkedProgram(program);
    GLCall(glValidateProgram(program));
    deleteShaders(compiledShaders);
    return program;
}

void Shader::logIncorrectlyCompiledShader(const Shader::ShaderSourceCode& shader, unsigned id)
{
    auto length = 0;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    const auto message = (char*)alloca(length * sizeof(char));
    GLCall(glGetShaderInfoLog(id, length, &length, message));
    spdlog::error("Failed to compile {} shader!\n Filepath: {}\n Opengl error:\n {}",
                  toString(shader.shaderSource.shaderType), shader.shaderSource.filePath, message);
}

unsigned Shader::compileShader(const ShaderSourceCode& shader)
{
    const auto shaderType = toOpenGl(shader.shaderSource.shaderType);
    const auto shaderSource = shader.sourceCode.c_str();

    GLCall(auto id = static_cast<unsigned int>(glCreateShader(shaderType)));
    GLCall(glShaderSource(id, 1, &shaderSource, nullptr));
    GLCall(glCompileShader(id));

    auto isShaderCompiledCorrectly = 0;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &isShaderCompiledCorrectly));
    if (not isShaderCompiledCorrectly)
    {
        logIncorrectlyCompiledShader(shader, id);
        GLCall(glDeleteShader(id));
        return GL_INVALID_VALUE;
    }

    return id;
}

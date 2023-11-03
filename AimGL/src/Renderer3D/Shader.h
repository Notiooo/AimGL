#pragma once


/**
 * \brief A type describing the type of shader available in opengl
 */
enum class ShaderType
{
    VertexShader,
    FragmentShader,
    // more types can be supported later on...
};

/**
 * \brief Data describing the necessary parameters for loading the shader.
 * Its type and the path to its file.
 */
struct ShaderSource
{
    ShaderType shaderType;
    std::string filePath;
};

/**
 * \brief Shader abstraction wrapping opengl functions.
 * Allows the program to be loaded into the GPU for various types of shaders.
 * It also allows to set uniforms, and has proper caching of uniforms.
 */
class Shader
{
private:
    struct ShaderSourceCode
    {
        ShaderSource shaderSource;
        std::string sourceCode;
    };

public:
    /**
     * \brief It takes a list of shaders, where each shader consists of
     * a shader type and a file path. Example:
     *
     * Shader({ShaderType::VertexShader, "resources/Shaders/basic.vs"},
              {ShaderType::FragmentShader, "resources/Shaders/basic.fs"})
     *
     * \param shaders List of shaders, where one shader is the type and path to the file
     */
    Shader(std::initializer_list<ShaderSource> shaders);

    Shader(const Shader&) = delete;
    Shader(Shader&&) noexcept = default;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) noexcept = default;
    ~Shader();

    /**
     * \brief Binds a shader object
     */
    void bind() const;

    /**
     * \brief Unbinds a shader object
     */
    void unbind() const;

    void setUniform(const std::string& name, float f1, float f2, float f3, float f4);
    void setUniform(const std::string& name, float f1, float f2, float f3);
    void setUniform(const std::string& name, float f1, float f2);
    void setUniform(const std::string& name, float f1);
    void setUniform(const std::string& name, int i1, int i2, int i3, int i4);
    void setUniform(const std::string& name, int i1, int i2, int i3);
    void setUniform(const std::string& name, int i1, int i2);
    void setUniform(const std::string& name, int i1);


private:
    /**
     * \brief It attaches the source code read from the file to the shader,
     * which can be further used to load it into opengl.
     * \param shaders Vector of shaders, where one shader is the type and path to the file
     * \return Vector of shaders, where one shader is the type, path to the file and source code
     */
    std::vector<ShaderSourceCode> parseShaders(const std::vector<ShaderSource>& shaders);

    /**
     * \brief Compiles a list of shaders, and returns a list of shader IDs
     * \param shaders Vector of shaders, where one shader is the type, path to the file and source
     * code \return List of compiled opnegl shader IDs
     */
    std::vector<unsigned> compileShaders(const std::vector<Shader::ShaderSourceCode>& shaders);

    /**
     * \brief Attaches all given compiled shaders to the specified program
     * \param program Program object to which a shader object will be attached.
     * \param compiledShaders List of shader objects that are to be attached.
     */
    void attachShaders(unsigned program, const std::vector<unsigned>& compiledShaders);

    /**
     * \brief Informs in case of incorrect linking of the program
     * \param program The program object that was linked.
     */
    void logInCaseOfIncorrectlyLinkedProgram(unsigned program);

    /**
     * \brief Removes compiled shaders
     * \param compiledShaders List of compiled opnegl shader IDs
     */
    void deleteShaders(const std::vector<unsigned>& compiledShaders);

    /**
     * \brief Returns the locations of a given uniform (by name)
     * \param name Name of uniform
     * \return Location, or -1 in case of failure
     */
    unsigned getUniformLocation(const std::string& name);

    /**
     * \brief Creates a shader based on shader types and source code
     * \param shaders Vector of shaders, where one shader is the type, path to the file and source
     * code \return Id of created program
     */
    unsigned createShader(const std::vector<ShaderSourceCode>& shaders);

    /**
     * \brief Informs in case of incorrect compiling of the program
     * \param shader Shader that is made of the type, path to the file and source code
     * \param id Program id
     */
    void logIncorrectlyCompiledShader(const ShaderSourceCode& shader, unsigned id);

    /**
     * \brief Compiles a shader, and returns a shader IDs
     * \param shader Shader that is made of the type, path to the file and source code
     * \return Compiled opnegl shader ID
     */
    unsigned compileShader(const ShaderSourceCode& shader);

private:
    unsigned int mRendererId;
    std::unordered_map<std::string, int> mUniformLocationCache;
};

/**
 * \brief Converts shader type in enum form to opengl equivalent
 * \param shaderType Internal enum specifying shader types
 * \return Opengl equivalent as unsigned
 */
inline unsigned int toOpenGl(const ShaderType& shaderType)
{
    switch (shaderType)
    {
        case ShaderType::VertexShader: return GL_VERTEX_SHADER;
        case ShaderType::FragmentShader: return GL_FRAGMENT_SHADER;
        default:
            spdlog::error("Undefined shader! Returning invalid value");
            return GL_INVALID_VALUE;
    }
}

/**
 * \brief Converts shader type in enum form to string equivalent
 * \param Internal enum specifying shader types
 * \return String equivalent
 */
inline std::string toString(const ShaderType& shaderType)
{
    switch (shaderType)
    {
        case ShaderType::VertexShader: return "VertexShader";
        case ShaderType::FragmentShader: return "FragmentShader";
        default: spdlog::error("Undefined shader! Returning invalid value"); return "Undefined";
    }
}
#include "Graphics/Shader.h"

#include <Core/Core.h>
#include <Core/Logger.h>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace an::gfx;

namespace
{

std::string readFile(const std::string &filepath)
{
    std::string result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    if(in)
    {
        in.seekg(0, std::ios::end);
        size_t size = in.tellg();
        if(size != -1)
        {
            result.resize(size);
            in.seekg(0, std::ios::beg);
            in.read(&result[0], size);
            in.close();
        }
        else
        {
            AN_ERROR("Cannot read {0}.", filepath);
        }
    }
    else
    {
        AN_ERROR("COuld not open file: {0}", filepath);
    }

    return result;
}

} // namespace

//--------------------------------------------------------------------------------------------------
Shader::Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath)
{
    const auto vertexSource = readFile(vertexFilePath);
    const auto fragmentSource = readFile(fragmentFilePath);

    init(vertexSource, fragmentSource);
}

//--------------------------------------------------------------------------------------------------
Shader::~Shader()
{
    glDeleteProgram(m_rendererID);
}

//--------------------------------------------------------------------------------------------------
void Shader::bind() const
{
    glUseProgram(m_rendererID);
}

//--------------------------------------------------------------------------------------------------
void Shader::unbind() const
{
    glUseProgram(0);
}

//--------------------------------------------------------------------------------------------------
void Shader::init(const std::string &vertexSource, const std::string &fragmentSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(vertexShader);

        AN_ERROR("{0}", infoLog.data());
        AN_ASSERT(false, "Vertex shader compilation failed.");

        return;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);

        AN_ERROR("{0}", infoLog.data());
        AN_ASSERT(false, "Fragment shader compilation failed.");

        return;
    }

    GLuint program = glCreateProgram();
    m_rendererID = program;

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        AN_ERROR("{0}", infoLog.data());
        AN_ASSERT(false, "Shader link failed.");

        return;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
}

//--------------------------------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), static_cast<int>(value));
}

//--------------------------------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), value);
}

//--------------------------------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_rendererID, name.c_str()), value);
}

//--------------------------------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_rendererID, name.c_str()), x, y);
}

//--------------------------------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, &value[0]);
}

//--------------------------------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_rendererID, name.c_str()), x, y, z);
}

//--------------------------------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, &value[0]);
}

//--------------------------------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_rendererID, name.c_str()), x, y, z, w);
}

//--------------------------------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, &value[0]);
}

//--------------------------------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

//--------------------------------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

//--------------------------------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

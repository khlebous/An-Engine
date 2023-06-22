#include "Graphics/Shader.h"

#include <Core/Core.h>
#include <Core/Logger.h>
#include <glad/glad.h>
#include <vector>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

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

void Shader::uploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
{
    GLint location = glGetUniformLocation(m_rendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

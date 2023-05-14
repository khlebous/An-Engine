#include "AnEngine/GraphicsContext.h"

#include <Core/Core.h>

#include <glad/glad.h>

using namespace an;

//--------------------------------------------------------------------------------------------------
OpenGLContext::OpenGLContext(GLFWwindow *window)
    : m_window{window}
{
}

//--------------------------------------------------------------------------------------------------
void OpenGLContext::init()
{
    glfwMakeContextCurrent(m_window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    AN_ASSERT(status, "Can't load glad.");
}

//--------------------------------------------------------------------------------------------------
void OpenGLContext::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

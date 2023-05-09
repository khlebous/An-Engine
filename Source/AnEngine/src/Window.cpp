#include "AnEngine/Window.h"

#include "AnEngine/GraphicsContext.h"
#include "AnEngine/Core.h"

#include <Core/Logger.h>

using namespace an;

//--------------------------------------------------------------------------------------------------
Window::Window(const std::string &name, unsigned int width, unsigned int height)
    : m_name {name}, m_width {width}, m_heigth {height}
{
    init();
    AN_INFO("Window created. name [{0}] size ({1}, {2})", m_name, m_width, m_heigth);
}

//--------------------------------------------------------------------------------------------------
Window::~Window()
{
    glfwDestroyWindow(m_glfwWindow);
}

//--------------------------------------------------------------------------------------------------
void Window::setVSync(bool enabled)
{
    if(enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_vSync = enabled;
}

//--------------------------------------------------------------------------------------------------
bool Window::isVSync() const
{
    return m_vSync;
}

//--------------------------------------------------------------------------------------------------
void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_glfwWindow);
}

//--------------------------------------------------------------------------------------------------
void Window::init()
{
    static bool sGlfwInitialized = false;
    if(!sGlfwInitialized)
    {
        int success = glfwInit();
        AN_ASSERT(success, "Can't create glfw window.");

        sGlfwInitialized = true;
    }

    m_glfwWindow = glfwCreateWindow((int)m_width, m_heigth, m_name.c_str(), nullptr, nullptr);
    m_graphicsContext = std::make_unique<an::OpenGLContext>(m_glfwWindow);
    m_graphicsContext->init();

    setVSync(true);
}

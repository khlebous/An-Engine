#include "Engine/Window.h"

#include "Engine/GraphicsContext.h"

#include <Core/Core.h>
#include <Core/KeyEvent.h>
#include <Core/Logger.h>
#include <Core/MouseEvent.h>
#include <Core/WindowEvent.h>
#include <GLFW/glfw3.h>

using namespace an;

struct Window::Impl
{
    GLFWwindow *m_glfwWindow;
};

//--------------------------------------------------------------------------------------------------
Window::Window(const std::string &name, unsigned int width, unsigned int height)
    : m_pImpl {std::make_unique<Window::Impl>()}
{
    m_data.m_name = name;
    m_data.m_width = width;
    m_data.m_height = height;

    init();
    AN_INFO(
        "Window created. name [{0}] size ({1}, {2})",
        m_data.m_name,
        m_data.m_width,
        m_data.m_height);
}

//--------------------------------------------------------------------------------------------------
Window::~Window()
{
    glfwDestroyWindow(m_pImpl->m_glfwWindow);
}

//--------------------------------------------------------------------------------------------------
void Window::setVSync(bool enabled)
{
    if(enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_data.m_vSync = enabled;
}

//--------------------------------------------------------------------------------------------------
bool Window::isVSync() const
{
    return m_data.m_vSync;
}

//--------------------------------------------------------------------------------------------------
void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_pImpl->m_glfwWindow);
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

    m_pImpl->m_glfwWindow = glfwCreateWindow(
        (int)m_data.m_width, (int)m_data.m_height, m_data.m_name.c_str(), nullptr, nullptr);
    m_graphicsContext = std::make_unique<an::OpenGLContext>(m_pImpl->m_glfwWindow);
    m_graphicsContext->init();

    glfwSetWindowUserPointer(m_pImpl->m_glfwWindow, &m_data);
    setVSync(true);

    glfwSetWindowCloseCallback(
        m_pImpl->m_glfwWindow,
        [](GLFWwindow *window)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.m_eventCallback(event);
        });

    glfwSetWindowSizeCallback(
        m_pImpl->m_glfwWindow,
        [](GLFWwindow *window, int width, int height)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            data.m_width = width;
            data.m_height = height;

            WindowResizeEvent event(width, height);
            data.m_eventCallback(event);
        });

    glfwSetKeyCallback(
        m_pImpl->m_glfwWindow,
        [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.m_eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.m_eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.m_eventCallback(event);
                    break;
                }
            }
        });

    glfwSetCharCallback(
        m_pImpl->m_glfwWindow,
        [](GLFWwindow *window, unsigned int keycode)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.m_eventCallback(event);
        });

    glfwSetMouseButtonCallback(
        m_pImpl->m_glfwWindow,
        [](GLFWwindow *window, int button, int action, int mods)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.m_eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.m_eventCallback(event);
                    break;
                }
            }
        });

    glfwSetScrollCallback(
        m_pImpl->m_glfwWindow,
        [](GLFWwindow *window, double xOffset, double yOffset)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            MouseScrollEvent event((float)xOffset, (float)yOffset);
            data.m_eventCallback(event);
        });

    glfwSetCursorPosCallback(
        m_pImpl->m_glfwWindow,
        [](GLFWwindow *window, double xPos, double yPos)
        {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.m_eventCallback(event);
        });
}

void *Window::getNativeWindow()
{
    return m_pImpl->m_glfwWindow;
}

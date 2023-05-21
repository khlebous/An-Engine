#include "Engine/Application.h"

#include "Engine/ImguiLayer.h"

#include <Core/Core.h>
#include <Core/Event.h>
#include <Core/WindowEvent.h>
#include <GLFW/glfw3.h>
#include <Graphics/BufferLayout.h>
#include <Graphics/Framebuffer.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shader.h>
#include <Graphics/VertexArray.h>
#include <Graphics/VertexBuffer.h>

using namespace an;

Application *Application::m_instance = nullptr;

//--------------------------------------------------------------------------------------------------
Application::Application()
{
    AN_ASSERT(!m_instance, "Instance already exists!");
    m_instance = this;
    m_window = std::make_unique<an::Window>("An Engine");
    m_window->setEventCallback(BIND_EVENT_FN(Application::onEvent));

    auto imguiOverlay = std::make_unique<an::ImguiLayer>();
    m_imguiOverlay = imguiOverlay.get();
    m_layerStack.pushOverlay(std::move(imguiOverlay));
}

//--------------------------------------------------------------------------------------------------
void Application::run()
{


    while(m_isRunning)
    {
        
        if(!m_isMinimized)
        {
            for(auto &layer : m_layerStack)
                layer->onUpdate();

            m_imguiOverlay->begin();
            for(auto &layer : m_layerStack)
                layer->onImgui();
            m_imguiOverlay->end();

            m_window->onUpdate();
        }
    }
}

void Application::close()
{
    m_isRunning = false;
}

void Application::onEvent(Event &event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::onWindowResize));

    for(auto it = m_layerStack.end(); it != m_layerStack.begin();)
    {
        (*--it)->onEvent(event);
        if(event.isHandled)
            break;
    }
}

bool Application::onWindowClose(WindowCloseEvent &event)
{
    m_isRunning = false;

    return true;
}

bool Application::onWindowResize(WindowResizeEvent &event)
{
    if(event.getWidth() == 0 || event.getHeight() == 0)
    {
        m_isMinimized = true;
        return false;
    }

    m_isMinimized = false;
    gfx::Renderer::onWindowResize(event.getWidth(), event.getHeight());

    return false;
}

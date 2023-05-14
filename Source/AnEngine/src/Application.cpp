#include "AnEngine/Application.h"

#include "AnEngine/ImguiLayer.h"

#include <Core/Core.h>
#include <GLFW/glfw3.h>
#include <Graphics/Renderer.h>
#include <Graphics/BufferLayout.h>
#include <Graphics/IndexBuffer.h>
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

    auto imguiOverlay = std::make_unique<an::ImguiLayer>();
    m_layerStack.pushOverlay(std::move(imguiOverlay));
}

//--------------------------------------------------------------------------------------------------
void Application::run()
{
    std::unique_ptr<an::gfx::Shader> shader;

    std::string vertexSource = R"(
        #version 330 core
            
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec4 v_Color;

        void main()
        {
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSource = R"(
        #version 330 core
            
        layout(location = 0) out vec4 color;
        
        in vec4 v_Color;
        
        void main()
        {
            color = v_Color;
        }
    )";

    shader.reset(new gfx::Shader(vertexSource, fragmentSource));

    auto vertArray = std::make_unique<gfx::VertexArray>();

    std::vector<gfx::BufferElement> elements;
    elements.reserve(2U);
    elements.emplace_back("a_Position", gfx::ShaderDataType::FLOAT3);
    elements.emplace_back("a_Color", gfx::ShaderDataType::FLOAT4);
    gfx::BufferLayout bufferLayout(std::move(elements));

    constexpr int vertexCount = 7;
    float vertices[3 * vertexCount] = {-0.5f, -0.5f, 0.0f, 0.0, 1.0, 1.0, 1.0,
                                       0.5f,  -0.5f, 0.0f, 1.0, 0.0, 1.0, 1.0,
                                       0.0f,  0.5f,  0.0f, 1.0, 1.0, 0.0, 1.0};
    auto vertexBuffer =
        std::make_unique<gfx::VertexBuffer>(vertices, 3 * vertexCount, std::move(bufferLayout));

    std::vector<std::unique_ptr<gfx::VertexBuffer>> vertBuffers;
    vertBuffers.push_back(std::move(vertexBuffer));

    vertArray->bind();
    unsigned int indices[vertexCount] = {0, 1, 2};
    auto indexBuffer = std::make_unique<gfx::IndexBuffer>(indices, 3);

    vertArray->setVertexBuffers(std::move(vertBuffers));
    vertArray->setIndexBuffer(std::move(indexBuffer));

    gfx::Renderer::setClearColor(0.6f, 0.6f, 0.6f, 1.0f);

    while(m_isRunning)
    {
        gfx::Renderer::clear();
        gfx::Renderer::submit(vertArray, shader);

        for(auto &layer : m_layerStack)
            layer->onUpdate();

        m_window->onUpdate();
    }
}

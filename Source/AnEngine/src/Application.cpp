#include "AnEngine/Application.h"

#include "AnEngine/ImguiLayer.h"

#include <Core/Core.h>
#include <GLFW/glfw3.h>
#include <Graphics/BufferLayout.h>
#include <Graphics/IndexBuffer.h>
#include <Graphics/Shader.h>
#include <Graphics/VertexBuffer.h>
#include <glad/glad.h>

using namespace an;

namespace
{

static GLenum toOpenGlType(an::gfx::ShaderDataType type)
{
    switch(type)
    {
        case an::gfx::ShaderDataType::FLOAT:
        case an::gfx::ShaderDataType::FLOAT2:
        case an::gfx::ShaderDataType::FLOAT3:
        case an::gfx::ShaderDataType::FLOAT4:
        case an::gfx::ShaderDataType::MAT3x3:
        case an::gfx::ShaderDataType::MAT4x4:
            return GL_FLOAT;
        case an::gfx::ShaderDataType::INT:
        case an::gfx::ShaderDataType::INT2:
        case an::gfx::ShaderDataType::INT3:
        case an::gfx::ShaderDataType::INT4:
            return GL_INT;
        case an::gfx::ShaderDataType::BOOL:
            return GL_BOOL;
    }

    AN_ASSERT(false, "Unknown ShaderDataType.");
    return GL_NONE;
}

static GLboolean toOpenGlType(bool val)
{
    return val ? GL_TRUE : GL_FALSE;
}

} // namespace

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
    unsigned int vertexArray;
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

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    constexpr int vertexCount = 7;
    float vertices[3 * vertexCount] = {
        -0.5f, -0.5f, 0.0f, 0.0, 1.0, 1.0, 1.0,
         0.5f, -0.5f, 0.0f, 1.0, 0.0, 1.0, 1.0,
         0.0f,  0.5f, 0.0f, 1.0, 1.0, 0.0, 1.0};
    auto vertexBuffer = std::make_unique<gfx::VertexBuffer>(vertices, 3 * vertexCount);

    std::vector<gfx::BufferElement> elements;
    elements.reserve(2U);
    elements.emplace_back("a_Position", gfx::ShaderDataType::FLOAT3);
    elements.emplace_back("a_Color", gfx::ShaderDataType::FLOAT4);
     gfx::BufferLayout bufferLayout(std::move(elements));

     auto &layoutElements = bufferLayout.elements();
     for(std::size_t idx {}; idx < layoutElements.size(); ++idx)
    {
         const auto &currEl = layoutElements[idx];
         glEnableVertexAttribArray(idx);
         glVertexAttribPointer(
             idx,
             currEl.componentCount(),
             toOpenGlType(currEl.type()),
             toOpenGlType(currEl.normalized()),
             bufferLayout.stride(),
             reinterpret_cast<void*>(currEl.offset()));
     }

    unsigned int indices[vertexCount] = {0, 1, 2};
    auto indexBuffer = std::make_unique<gfx::IndexBuffer>(indices, 3);

    while(m_isRunning)
    {
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->bind();
        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, indexBuffer->count(), GL_UNSIGNED_INT, nullptr);

        for(auto &layer : m_layerStack)
            layer->onUpdate();

        m_window->onUpdate();
    }
}

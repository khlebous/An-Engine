#include "AnEngine/Application.h"

#include "AnEngine/ImguiLayer.h"

#include <Core/Core.h>
#include <GLFW/glfw3.h>
#include <Graphics/Shader.h>
#include <Graphics/VertexBuffer.h>
#include <glad/glad.h>

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
    unsigned int vertexArray, indexBuffer;
    std::unique_ptr<an::gfx::Shader> shader;

    std::string vertexSource = R"(
        #version 330 core
            
        layout(location = 0) in vec3 a_Position;
        out vec3 v_Position;
        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSource = R"(
        #version 330 core
            
        layout(location = 0) out vec4 color;
        in vec3 v_Position;
        void main()
        {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
        }
    )";

    shader.reset(new gfx::Shader(vertexSource, fragmentSource));

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    constexpr int vertexCount = 3;
    float vertices[3 * vertexCount] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    auto vertexBuffer = std::make_unique<gfx::VertexBuffer>(vertices, sizeof(vertices));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, vertexCount, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    unsigned int indices[vertexCount] = {0, 1, 2};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    while(m_isRunning)
    {
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->bind();
        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        for(auto &layer : m_layerStack)
            layer->onUpdate();

        m_window->onUpdate();
    }
}

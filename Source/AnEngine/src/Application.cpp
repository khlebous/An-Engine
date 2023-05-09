#include "AnEngine/Application.h"

#include "AnEngine/Core.h"
#include "AnEngine/ImguiLayer.h"

#include <GLFW/glfw3.h>
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
    unsigned int vertexArray, vertexBuffer, indexBuffer;

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    constexpr int vertexCount = 3;
    float vertices[3 * vertexCount] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

        glBindVertexArray(vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        for(auto &layer : m_layerStack)
            layer->onUpdate();

        m_window->onUpdate();
    }
}

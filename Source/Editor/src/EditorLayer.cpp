#include "Editor/EditorLayer.h"

#include <Graphics/Renderer.h>
#include <imgui/imgui.h>

using namespace an::ed;

//--------------------------------------------------------------------------------------------------
EditorLayer::EditorLayer() : m_vertArray {std::make_unique<gfx::VertexArray>()}
{
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

    m_shader = std::make_unique<gfx::Shader>(vertexSource, fragmentSource);

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

    m_vertArray->bind();
    unsigned int indices[vertexCount] = {0, 1, 2};
    auto indexBuffer = std::make_unique<gfx::IndexBuffer>(indices, 3);

    m_vertArray->setVertexBuffers(std::move(vertBuffers));
    m_vertArray->setIndexBuffer(std::move(indexBuffer));
    gfx::Renderer::setClearColor(0.6f, 0.6f, 0.6f, 1.0f);

    gfx::FramebufferSpecification fbSpecification;
    fbSpecification.m_width = 1280;
    fbSpecification.m_height = 720;
    m_framebuffer = std::make_unique<gfx::Framebuffer>(fbSpecification);
}

//--------------------------------------------------------------------------------------------------
void EditorLayer::onUpdate()
{
    gfx::Renderer::clear();

    m_framebuffer->bind();
    gfx::Renderer::clear();
    gfx::Renderer::submit(m_vertArray, m_shader);
    m_framebuffer->unbind();
}

//--------------------------------------------------------------------------------------------------
void EditorLayer::onImgui()
{
    ImGui::DockSpaceOverViewport();

    ImGui::Begin("Viewport");
    {
        uint32_t textureId = m_framebuffer->colorAttachmentRendererID();
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ImGui::Image(
            (void *)textureId,
            ImVec2 {viewportPanelSize.x, viewportPanelSize.y},
            ImVec2 {0, 1},
            ImVec2 {1, 0});
    }
    ImGui::End();

    ImGui::Begin("Viewport2");
    {
        uint32_t textureId = m_framebuffer->colorAttachmentRendererID();
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ImGui::Image(
            (void *)textureId,
            ImVec2 {viewportPanelSize.x, viewportPanelSize.y},
            ImVec2 {0, 1},
            ImVec2 {1, 0});
    }
    ImGui::End();
}

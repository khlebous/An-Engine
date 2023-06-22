#include "Editor/EditorLayer.h"

#include <Core/Core.h>
#include <Core/Event.h>
#include <Core/KeyCodes.h>
#include <Core/MouseButtonCodes.h>
#include <Core/MouseEvent.h>
#include <Engine/Input.h>
#include <Graphics/Renderer.h>
#include <config.h>
#include <imgui/imgui.h>

using namespace an::ed;

//--------------------------------------------------------------------------------------------------
EditorLayer::EditorLayer() : m_camera({0.5f, 0.0f, 5.0f})
{
    std::string vertexFilePath = an::config::resourcesPath + "shader.vs";
    std::string fragmentFilePath = an::config::resourcesPath + "shader.fs";
    m_shader = std::make_shared<gfx::Shader>(vertexFilePath, fragmentFilePath);

    gfx::Renderer::setClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    gfx::Renderer::enableDepthTest();

    gfx::FramebufferSpecification fbSpecification;
    fbSpecification.m_width = 1280;
    fbSpecification.m_height = 720;
    m_framebuffer = std::make_unique<gfx::Framebuffer>(fbSpecification);

    m_model = std::make_unique<gfx::Model>(an::config::resourcesPath + "suzanne.obj");
    m_model->setShader(m_shader);
}

//--------------------------------------------------------------------------------------------------
void EditorLayer::onUpdate()
{
    // @todo change to delta time
    float cameraMoveSpeed = 0.05f;

    if(an::Input::isKeyPressed(AN_KEY_LEFT) || an::Input::isKeyPressed(AN_KEY_A))
        m_camera.processKeyboard(an::gfx::Camera::Direction::LEFT, cameraMoveSpeed);
    else if(an::Input::isKeyPressed(AN_KEY_RIGHT) || an::Input::isKeyPressed(AN_KEY_D))
        m_camera.processKeyboard(an::gfx::Camera::Direction::RIGHT, cameraMoveSpeed);
    else if(an::Input::isKeyPressed(AN_KEY_DOWN) || an::Input::isKeyPressed(AN_KEY_S))
        m_camera.processKeyboard(an::gfx::Camera::Direction::BACKWARD, cameraMoveSpeed);
    else if(an::Input::isKeyPressed(AN_KEY_UP) || an::Input::isKeyPressed(AN_KEY_W))
        m_camera.processKeyboard(an::gfx::Camera::Direction::FORWARD, cameraMoveSpeed);

    gfx::Renderer::clear();

    m_framebuffer->bind();
    gfx::Renderer::clear();
    gfx::Renderer::begin(m_camera);
    gfx::Renderer::submit(m_model);
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

        m_camera.setAspect(viewportPanelSize.x / viewportPanelSize.y);
    }
    ImGui::End();

    ImGui::Begin("Inspector");
    {
        ImGui::Text("Camera");
        ImGui::DragFloat3("Position", &m_camera.getPosition().x, 0.1);
    }
    ImGui::End();
}

void EditorLayer::onEvent(Event &event)
{
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<MouseScrollEvent>(BIND_EVENT_FN(EditorLayer::onMouseScrollEvent));
    dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FN(EditorLayer::onMouseMovedEvent));
    dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(EditorLayer::onWindowResizeEvent));
}

bool EditorLayer::onMouseScrollEvent(MouseScrollEvent &mouseScrollEvent)
{
    m_camera.processMouseScroll(mouseScrollEvent.getYOffset());
    return true;
}

bool EditorLayer::onMouseMovedEvent(MouseMovedEvent &mouseMovedEvent)
{
    if(an::Input::isMouseButtonPressed(AN_MOUSE_BUTTON_RIGHT))
    {
        m_camera.processMouseMovement(
            prevFrameMousePos.x - mouseMovedEvent.getX(),
            mouseMovedEvent.getY() - prevFrameMousePos.y);
    }

    prevFrameMousePos = {mouseMovedEvent.getX(), mouseMovedEvent.getY()};

    return true;
}

bool EditorLayer::onWindowResizeEvent(WindowResizeEvent &windowResizeEvent) 
{
    m_camera.setAspect(windowResizeEvent.getWidth() / windowResizeEvent.getHeight());

    return true;
}

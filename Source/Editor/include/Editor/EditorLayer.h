#pragma once

#include <Core/MouseEvent.h>
#include <Core/WindowEvent.h>
#include <Engine/Layer.h>
#include <Graphics/Camera.h>
#include <Graphics/Framebuffer.h>
#include <Graphics/Model.h>
#include <Graphics/Shader.h>
#include <Graphics/VertexArray.h>
#include <memory>

namespace an::ed
{

class EditorLayer : public Layer
{
  public:
    EditorLayer();

    void onUpdate(double deltaTime) final;
    void onImgui() final;

    void onEvent(Event &event) override;

  private:
    bool onMouseScrollEvent(MouseScrollEvent &mouseScrollEvent);
    bool onMouseMovedEvent(MouseMovedEvent &mouseMovedEvent);
    bool onWindowResizeEvent(WindowResizeEvent &windowResizeEvent);

  private:
    std::shared_ptr<gfx::Shader> m_shader;
    std::unique_ptr<gfx::Framebuffer> m_framebuffer;
    std::unique_ptr<gfx::Model> m_model;
    
    gfx::Camera m_camera;
    glm::vec3 m_lightPos {10.0f, 0.0f, 2.5f};
    glm::vec3 m_lightColor {1.0f, 1.0f, 1.0f};

    glm::vec2 prevFrameMousePos {-1, -1};
};

} // namespace an::ed

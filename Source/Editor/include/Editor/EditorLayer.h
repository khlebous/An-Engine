#pragma once

#include <Core/MouseEvent.h>
#include <Core/WindowEvent.h>
#include <Engine/Layer.h>
#include <Graphics/Camera.h>
#include <Graphics/Framebuffer.h>
#include <Graphics/Light.h>
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
    std::shared_ptr<gfx::Light> m_light;
    std::unique_ptr<gfx::Framebuffer> m_framebuffer;
    std::unique_ptr<gfx::Model> m_model;

    gfx::Camera m_camera;

    glm::vec2 prevFrameMousePos {-1, -1};
};

} // namespace an::ed

#pragma once

#include <Engine/Layer.h>
#include <Graphics/Shader.h>
#include <Graphics/VertexArray.h>
#include <Graphics/Framebuffer.h>

#include <memory>

namespace an::ed
{

class EditorLayer : public Layer
{
  public:
    EditorLayer();

    void onUpdate() final;
    void onImgui() final;

  private:
    std::unique_ptr<gfx::VertexArray> m_vertArray;
    std::unique_ptr<gfx::Shader> m_shader;
    std::unique_ptr<gfx::Framebuffer> m_framebuffer;
};

} // namespace an

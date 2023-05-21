#ifndef AN_GRAPHICS_FRAMEBUFFER
#define AN_GRAPHICS_FRAMEBUFFER

#include <cstdint>

namespace an::gfx
{

struct FramebufferSpecification
{
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_samples = 1;

    bool m_swapChainTarget = false;
};

class Framebuffer
{
  public:
    Framebuffer(const FramebufferSpecification &specification);
    ~Framebuffer();

    void invalidate();

    void bind();
    void unbind();

    uint32_t colorAttachmentRendererID() const { return m_colorAttachment; }
    const FramebufferSpecification &specification() const { return m_specification; }

  private:
    uint32_t m_id;
    uint32_t m_colorAttachment;
    uint32_t m_depthAttachment;

    FramebufferSpecification m_specification;
};
} // namespace an

#endif // AN_GRAPHICS_FRAMEBUFFER

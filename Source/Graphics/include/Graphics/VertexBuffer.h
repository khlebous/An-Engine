#ifndef AN_ENGINE_GRAPHICS_VERTEX_BUFFER
#define AN_ENGINE_GRAPHICS_VERTEX_BUFFER

#include <cstddef>
#include <cstdint>

namespace an::gfx
{

class VertexBuffer
{
  public:
    VertexBuffer(float *data, std::size_t count);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

  private:
    uint32_t m_rendererID;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_VERTEX_BUFFER

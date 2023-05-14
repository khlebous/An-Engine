#ifndef AN_ENGINE_GRAPHICS_VERTEX_BUFFER
#define AN_ENGINE_GRAPHICS_VERTEX_BUFFER

#include "Graphics/BufferLayout.h"

#include <cstddef>
#include <cstdint>

namespace an::gfx
{

class VertexBuffer
{
  public:
    VertexBuffer(float *data, std::size_t count, BufferLayout layout);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    const BufferLayout &layout() const { return m_layout; }

  private:
    unsigned int m_id;
    BufferLayout m_layout;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_VERTEX_BUFFER

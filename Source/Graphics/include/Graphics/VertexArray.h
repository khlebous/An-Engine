#ifndef AN_ENGINE_GRAPHICS_VERTEX_ARRAY
#define AN_ENGINE_GRAPHICS_VERTEX_ARRAY

#include <Graphics/IndexBuffer.h>
#include <Graphics/VertexBuffer.h>
#include <memory>
#include <vector>

namespace an::gfx
{

class VertexArray
{
  public:
    VertexArray();

    void bind() const;
    void unbind() const;

    const std::vector<std::unique_ptr<VertexBuffer>> &vertexBuffers() const;
    void setVertexBuffers(std::vector<std::unique_ptr<VertexBuffer>> vertBuffers);

    const std::unique_ptr<IndexBuffer> &indexBuffer() const { return m_indexBuffer; };
    void setIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffers);

  private:
    unsigned int m_id;
    std::vector<std::unique_ptr<VertexBuffer>> m_vertexBuffers;
    std::unique_ptr<IndexBuffer> m_indexBuffer;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_VERTEX_ARRAY

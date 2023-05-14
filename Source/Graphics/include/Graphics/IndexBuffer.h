#ifndef AN_ENGINE_GRAPHICS_INDEX_BUFFER
#define AN_ENGINE_GRAPHICS_INDEX_BUFFER

#include <cstddef>
#include <cstdint>

namespace an::gfx
{

class IndexBuffer
{
  public:
    IndexBuffer(uint32_t *data, std::size_t count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    std::size_t count() const { return m_count; }

  private:
    unsigned int m_id;
    std::size_t m_count;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_INDEX_BUFFER

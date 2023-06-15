#ifndef AN_ENGINE_GRAPHICS_BUFFER_LAYOUT
#define AN_ENGINE_GRAPHICS_BUFFER_LAYOUT

#include <Core/Core.h>
#include <string>

namespace an::gfx
{

enum class ShaderDataType
{
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    MAT3x3,
    MAT4x4,
    INT,
    INT2,
    INT3,
    INT4,
    BOOL
};

class BufferElement
{
    friend class BufferLayout;

  public:
    BufferElement(const std::string &name, ShaderDataType type, bool normalized = false);

    const std::string &name() const { return m_name; };
    ShaderDataType type() const { return m_type; };
    bool normalized() const { return m_normalized; };

    std::size_t size() const { return m_size; };
    std::size_t componentCount() const { return m_componentCount; };
    std::size_t offset() const { return m_offset; };

  private:
    std::string m_name;
    ShaderDataType m_type;
    bool m_normalized;

    std::size_t m_size;
    std::size_t m_componentCount;
    std::size_t m_offset;
};

class BufferLayout
{
  public:
    BufferLayout(std::vector<BufferElement> elements);

    [[no_discard]] std::size_t stride() const { return m_stride; }
    [[no_discard]] const std::vector<BufferElement> &elements() const { return m_elements; }
    
    [[no_discard]] std::size_t componentCount() const;

  private:
    std::vector<BufferElement> m_elements;
    std::size_t m_stride;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_BUFFER_LAYOUT

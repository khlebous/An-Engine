#include "Graphics/BufferLayout.h"

using namespace an::gfx;

namespace
{

std::size_t toSize(an::gfx::ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::FLOAT:
            return 4U;
        case ShaderDataType::FLOAT2:
            return 4U * 2U;
        case ShaderDataType::FLOAT3:
            return 4U * 3U;
        case ShaderDataType::FLOAT4:
            return 4U * 4U;
        case ShaderDataType::MAT3x3:
            return 4U * 3U * 3U;
        case ShaderDataType::MAT4x4:
            return 4U * 4U * 4U;
        case ShaderDataType::INT:
            return 4U;
        case ShaderDataType::INT2:
            return 4U * 2U;
        case ShaderDataType::INT3:
            return 4U * 3U;
        case ShaderDataType::INT4:
            return 4U * 4U;
        case ShaderDataType::BOOL:
            return 1U;
    }

    AN_ASSERT(false, "Unknown ShaderDataType.")
    return 0U;
}

std::size_t toComponentCount(an::gfx::ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::FLOAT:
            return 1U;
        case ShaderDataType::FLOAT2:
            return 2U;
        case ShaderDataType::FLOAT3:
            return 3U;
        case ShaderDataType::FLOAT4:
            return 4U;
        case ShaderDataType::MAT3x3:
            return 3U * 3U;
        case ShaderDataType::MAT4x4:
            return 4U * 4U;
        case ShaderDataType::INT:
            return 1U;
        case ShaderDataType::INT2:
            return 2U;
        case ShaderDataType::INT3:
            return 3U;
        case ShaderDataType::INT4:
            return 4U;
        case ShaderDataType::BOOL:
            return 1U;
    }

    AN_ASSERT(false, "Unknown ShaderDataType.")
    return 0U;
}

} // namespace

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

BufferElement::BufferElement(const std::string &name, ShaderDataType type, bool normalized)
    : m_name(name)
    , m_type(type)
    , m_normalized(normalized)
    , m_size(toSize(type))
    , m_componentCount(toComponentCount(type))
    , m_offset(0U)
{
}

//--------------------------------------------------------------------------------------------------
BufferLayout::BufferLayout(std::vector<BufferElement> elements)
    : m_elements(std::move(elements)), m_stride(0U)
{
    std::size_t offset {};
    for(auto &el : m_elements)
    {
        el.m_offset = offset;

        const auto currElSize = el.size();
        m_stride += currElSize;
        offset += currElSize;
    }
}

std::size_t BufferLayout::componentCount() const
{
    std::size_t componentCount{};
    for(const auto &bufElemnt : elements())
    {
        componentCount += bufElemnt.componentCount();
    }

    return componentCount;
}

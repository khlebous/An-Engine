#include "Graphics/VertexArray.h"

#include <Core/Core.h>
#include <glad/glad.h>

using namespace an::gfx;

namespace
{

static GLenum toOpenGlType(an::gfx::ShaderDataType type)
{
    switch(type)
    {
        case an::gfx::ShaderDataType::FLOAT:
        case an::gfx::ShaderDataType::FLOAT2:
        case an::gfx::ShaderDataType::FLOAT3:
        case an::gfx::ShaderDataType::FLOAT4:
        case an::gfx::ShaderDataType::MAT3x3:
        case an::gfx::ShaderDataType::MAT4x4:
            return GL_FLOAT;
        case an::gfx::ShaderDataType::INT:
        case an::gfx::ShaderDataType::INT2:
        case an::gfx::ShaderDataType::INT3:
        case an::gfx::ShaderDataType::INT4:
            return GL_INT;
        case an::gfx::ShaderDataType::BOOL:
            return GL_BOOL;
    }

    AN_ASSERT(false, "Unknown ShaderDataType.");
    return GL_NONE;
}

static GLboolean toOpenGlType(bool val)
{
    return val ? GL_TRUE : GL_FALSE;
}

} // namespace

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::setVertexBuffers(std::vector<std::unique_ptr<VertexBuffer>> vertBuffers)
{
    m_vertexBuffers = std::move(vertBuffers);
    bind();

    for(const auto &vertBuffer : m_vertexBuffers)
    {
        vertBuffer->bind();

        const auto &layout = vertBuffer->layout();
        const auto &layoutElements = layout.elements();
        for(std::size_t idx {}; idx < layoutElements.size(); ++idx)
        {
            const auto &currEl = layoutElements[idx];
            glEnableVertexAttribArray(idx);
            glVertexAttribPointer(
                idx,
                currEl.componentCount(),
                toOpenGlType(currEl.type()),
                toOpenGlType(currEl.normalized()),
                layout.stride(),
                reinterpret_cast<void *>(currEl.offset()));
        }
    }
}

void VertexArray::setIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer)
{
    bind();

    m_indexBuffer = std::move(indexBuffer);
    m_indexBuffer->bind();
}

const std::vector<std::unique_ptr<an::gfx::VertexBuffer>> &VertexArray::vertexBuffers() const
{
    return m_vertexBuffers;
}

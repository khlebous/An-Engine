#include "Graphics/VertexBuffer.h"

#include <glad/glad.h>

using namespace an::gfx;

//--------------------------------------------------------------------------------------------------
VertexBuffer::VertexBuffer(float *data, std::size_t count, BufferLayout layout)
    : m_layout(std::move(layout))
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
}

//--------------------------------------------------------------------------------------------------
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

//--------------------------------------------------------------------------------------------------
void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

//--------------------------------------------------------------------------------------------------
void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

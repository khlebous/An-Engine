#include "Graphics/IndexBuffer.h"

#include <Core/Core.h>
#include <glad/glad.h>

using namespace an::gfx;

//--------------------------------------------------------------------------------------------------
IndexBuffer::IndexBuffer(uint32_t *data, std::size_t count) : m_count(count)
{
    GLuint currVao = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, reinterpret_cast<GLint *>(&currVao));
    AN_ASSERT(currVao != 0, "No vertex array is bound.");

    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

//--------------------------------------------------------------------------------------------------
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_id);
}

//--------------------------------------------------------------------------------------------------
void IndexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

//--------------------------------------------------------------------------------------------------
void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

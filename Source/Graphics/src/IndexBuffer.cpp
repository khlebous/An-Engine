#include "Graphics/IndexBuffer.h"

#include <glad/glad.h>

using namespace an::gfx;

IndexBuffer::IndexBuffer(uint32_t *data, std::size_t count) : m_count(count)
{
    glGenBuffers(1, &m_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

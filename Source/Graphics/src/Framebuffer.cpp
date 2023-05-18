#include "Graphics/Framebuffer.h"

#include <glad/glad.h>
#include <Core/Core.h>

using namespace an::gfx;

Framebuffer::Framebuffer(const FramebufferSpecification &specification)
    : m_specification(specification)
{
    invalidate();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_id);
}

void Framebuffer::invalidate()
{
    glCreateFramebuffers(1, &m_id);
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
    glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        m_specification.m_width,
        m_specification.m_height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
    glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
    glTexStorage2D(
        GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.m_width, m_specification.m_height);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);

    AN_ASSERT(
        glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
        "Framebuffer is not complete.");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

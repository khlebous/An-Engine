#include "Graphics/Renderer.h"

#include <glad/glad.h>

using namespace an::gfx;

//--------------------------------------------------------------------------------------------------
void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
}

//--------------------------------------------------------------------------------------------------
void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

//--------------------------------------------------------------------------------------------------
void Renderer::submit(
    const std::unique_ptr<VertexArray> &vertArray, const std::unique_ptr<Shader> &shader)
{
    shader->bind();
    vertArray->bind();
    glDrawElements(GL_TRIANGLES, vertArray->indexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
}

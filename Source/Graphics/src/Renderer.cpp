#include "Graphics/Renderer.h"

#include "Graphics/Camera.h"
#include "Graphics/Model.h"

#include <glad/glad.h>

using namespace an::gfx;

Renderer::SceneData Renderer::sSceneData = Renderer::SceneData {};

//--------------------------------------------------------------------------------------------------
void Renderer::setClearColor(float r, float g, float b, float a)
{
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
}

//--------------------------------------------------------------------------------------------------
void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//--------------------------------------------------------------------------------------------------
void Renderer::enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------------------------------------------
void Renderer::disableDepthTest()
{
    glDisable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------------------------------------------
void Renderer::begin(const Camera &camera, const glm::vec3 &lightPos, const glm::vec3 &lightColor)
{
    sSceneData.projectionMatrix =
        glm::perspective(glm::radians(camera.getZoom()), camera.aspect(), camera.getNear(), camera.getFar());

    sSceneData.viewMatrix = camera.viewMatrix();
    sSceneData.cameraPosition = camera.getPosition();

    sSceneData.lightPos = lightPos;
    sSceneData.lightColor = lightColor;
}

//--------------------------------------------------------------------------------------------------
void Renderer::submit(const std::unique_ptr<Model> &model)
{
    const auto &shader = model->shader();
    shader->bind();
    shader->setMat4("u_view", sSceneData.viewMatrix);
    shader->setMat4("u_projection", sSceneData.projectionMatrix);
    shader->setMat4("u_model", model->modelMatrix());

    shader->setVec3("viewPos", sSceneData.cameraPosition);
    shader->setVec3("lightPos", sSceneData.lightPos);
    shader->setVec3("lightColor", sSceneData.lightColor);
    shader->setVec3("objectColor", model->color());

    for(const auto &mesh : model->meshes())
        Renderer::submit(mesh);
}

//--------------------------------------------------------------------------------------------------
void Renderer::submit(const Mesh &mesh)
{
    const auto &vertArray = mesh.vertArray();
    vertArray->bind();
    glDrawElements(GL_TRIANGLES, vertArray->indexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
}

//--------------------------------------------------------------------------------------------------
void Renderer::onWindowResize(unsigned int width, unsigned int height)
{
    glViewport(0, 0, width, height);
}

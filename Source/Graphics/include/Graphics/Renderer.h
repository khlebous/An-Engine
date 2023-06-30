#ifndef AN_ENGINE_GRAPHICS_RENDERER
#define AN_ENGINE_GRAPHICS_RENDERER

#include "Graphics/Light.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/Texture.h"

#include <glm/ext/matrix_float4x4.hpp>

namespace an::gfx
{

class Camera;

class Renderer
{
  public:
    static void setClearColor(float r, float g, float b, float a);
    static void clear();
    static void enableDepthTest();
    static void disableDepthTest();

    static void begin(const Camera &camera, std::shared_ptr<Light> light);
    static void submit(const std::unique_ptr<Model> &model);

    static void onWindowResize(unsigned int width, unsigned int height);

    static void drawQuad(const glm::vec2 &, const glm::vec2 &, const gfx::Texture &checkboxTexture, gfx::Shader &shader);

  private:
    static void submit(const Mesh &mesh);

  private:
    struct SceneData
    {
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 cameraPosition;

        std::shared_ptr<Light> light;
    };

    static SceneData sSceneData;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_RENDERER

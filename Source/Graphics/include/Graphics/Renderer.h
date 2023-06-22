#ifndef AN_ENGINE_GRAPHICS_RENDERER
#define AN_ENGINE_GRAPHICS_RENDERER

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

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

    static void begin(const Camera &camera);
    static void submit(const std::unique_ptr<Model> &model);

    static void onWindowResize(unsigned int width, unsigned int height);

  private:
    static void submit(const Mesh &mesh);

  private:
    struct SceneData
    {
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
    };

    static SceneData sSceneData;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_RENDERER

#ifndef AN_ENGINE_GRAPHICS_RENDERER
#define AN_ENGINE_GRAPHICS_RENDERER

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

namespace an::gfx
{

class Renderer
{
  public:
    static void setClearColor(float r, float g, float b, float a);
    static void clear();
    static void submit(
        const std::unique_ptr<VertexArray> &vertArray, const std::shared_ptr<Shader> &shader);
    static void submit(const std::unique_ptr<Model> &model);

    static void onWindowResize(unsigned int width, unsigned int height);

  private:
    static void submit(const Mesh &mesh);
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_RENDERER

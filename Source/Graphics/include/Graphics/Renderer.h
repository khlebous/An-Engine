#ifndef AN_ENGINE_GRAPHICS_RENDERER
#define AN_ENGINE_GRAPHICS_RENDERER

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
        const std::unique_ptr<VertexArray> &vertArray, const std::unique_ptr<Shader> &shader);
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_RENDERER

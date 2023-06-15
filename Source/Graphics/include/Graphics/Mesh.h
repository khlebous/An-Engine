#ifndef AN_GRAPHICS_MESH
#define AN_GRAPHICS_MESH

#include "Graphics/VertexArray.h"

namespace an::gfx
{

class Mesh
{
  public:
    Mesh(std::unique_ptr<VertexArray> vertArray);

    const std::unique_ptr<VertexArray> &vertArray() const { return m_vertArray; }

  private:
    std::unique_ptr<VertexArray> m_vertArray;
};

} // namespace an::gfx

#endif // AN_GRAPHICS_MESH

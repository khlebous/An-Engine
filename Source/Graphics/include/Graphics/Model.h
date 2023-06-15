#ifndef AN_GRAPHICS_MODEL
#define AN_GRAPHICS_MODEL

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"

namespace an::gfx
{

class Model
{
  public:
    Model(std::string const &path);

    const std::shared_ptr<Shader> &shader() { return m_shader; }
    void setShader(std::shared_ptr<Shader> shader) { m_shader = std::move(shader); }

    const std::vector<Mesh> &meshes() const { return m_meshes; };

  private:
    void load(std::string const &path);

  private:
    std::string m_directory;
    std::vector<Mesh> m_meshes;
    std::shared_ptr<Shader> m_shader;
};

} // namespace an::gfx

#endif

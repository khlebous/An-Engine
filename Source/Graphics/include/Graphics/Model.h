#ifndef AN_GRAPHICS_MODEL
#define AN_GRAPHICS_MODEL

#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

namespace an::gfx
{

class Model
{
  public:
    Model(std::string const &path);

    const std::shared_ptr<Shader> &shader() { return m_shader; }
    void setShader(std::shared_ptr<Shader> shader) { m_shader = std::move(shader); }

    const std::vector<Mesh> &meshes() const { return m_meshes; };
    const glm::mat4 &modelMatrix() const { return m_modelMatrix; }
    const glm::vec3 &color() const { return m_color; }

    const Material &material() const { return m_material; }
    Material &material() { return m_material; }

  private:
    void load(std::string const &path);

  private:
    std::string m_directory;
    std::vector<Mesh> m_meshes;
    std::shared_ptr<Shader> m_shader;

    Material m_material;
    glm::mat4 m_modelMatrix {glm::mat4(1.0f)};
    glm::vec3 m_color {1.0f};
};

} // namespace an::gfx

#endif

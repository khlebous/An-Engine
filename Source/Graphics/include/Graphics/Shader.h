#ifndef AN_ENGINE_GRAPHICS_SHADER
#define AN_ENGINE_GRAPHICS_SHADER

#include <string>

#include <glm/fwd.hpp>

namespace an::gfx
{

class Shader
{
  public:
    Shader(const std::string &vertexFilePath, const std::string &fragmentSourceFilePath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

  private:
    void init(const std::string &vertexSource, const std::string &fragmentSource);

  private:
    uint32_t m_rendererID;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_SHADER

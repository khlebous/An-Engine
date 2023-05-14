#ifndef AN_ENGINE_GRAPHICS_SHADER
#define AN_ENGINE_GRAPHICS_SHADER

#include <string>

namespace an::gfx
{

class Shader
{
  public:
    Shader(const std::string &vertexSource, const std::string &fragmentSource);
    ~Shader();

    void bind() const;
    void unbind() const;

  private:
    uint32_t m_rendererID;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_SHADER

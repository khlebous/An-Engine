#ifndef AN_ENGINE_GRAPHICS_SHADER
#define AN_ENGINE_GRAPHICS_SHADER

#include <string>

namespace an::gfx
{

class Shader
{
  public:
    Shader(const std::string &vertexFilePath, const std::string &fragmentSourceFilePath);
    ~Shader();

    void bind() const;
    void unbind() const;

  private:
    void init(const std::string &vertexSource, const std::string &fragmentSource);

  private:
    uint32_t m_rendererID;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_SHADER

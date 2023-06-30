#ifndef AN_ENGINE_GRAPHICS_TEXTURE
#define AN_ENGINE_GRAPHICS_TEXTURE

#include <utility>
#include <string>

namespace an::gfx
{

class Texture
{
  public:
    Texture(const std::string &_path);
    ~Texture();

    uint32_t GetWidth() const  { return width; };
    uint32_t GetHeight() const  { return height; };

    void Bind(uint32_t _slot = 0) const;

  private:
    std::string path;
    uint32_t width, height;
    uint32_t rendererID;
    unsigned int internalFormat, dataFormat;
};

} // namespace an

#endif // AN_ENGINE_GRAPHICS_TEXTURE

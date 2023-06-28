#ifndef AN_ENGINE_GRAPHICS_MATERIAL
#define AN_ENGINE_GRAPHICS_MATERIAL

#include <glm/ext/vector_float3.hpp>

namespace an::gfx
{

struct Material
{
    glm::vec3 ambient {0.0f, 0.0f, 0.0f};
    glm::vec3 diffuse {100.0f / 255.0f, 104.0f/ 255.0f, 102.0f/ 255.0f};
    glm::vec3 specular { 143.0f/ 255.0f, 107.0f/ 255.0f, 107.0f/ 255.0f};
    float shininess {4.7f};
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_MATERIAL

#ifndef AN_ENGINE_GRAPHICS_LIGHT
#define AN_ENGINE_GRAPHICS_LIGHT

#include <glm/ext/vector_float3.hpp>

namespace an::gfx
{

struct Light
{
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

} // namespace an::gfx

#endif // AN_ENGINE_GRAPHICS_LIGHT

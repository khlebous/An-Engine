#ifndef AN_GRAPHICS_CAMERA_H
#define AN_GRAPHICS_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace an::gfx
{

class Camera
{
  public:
    enum class Direction
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

  public:
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 viewMatrix() const;

    void processKeyboard(Direction direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yoffset);

    glm::vec3 &getPosition() { return m_position; }
    const glm::vec3 &getPosition() const { return m_position; }

    float getZoom() const { return m_zoom; }

    void setAspect(float aspect) { m_aspect = aspect; }
    float aspect() const { return m_aspect; }

    float getNear() const { return m_near; }
    void setNear(float val) { m_near = val; }

    float getFar() const { return m_far; }
    void setFar(float val) { m_far = val; }

  private:
    void updateCameraVectors();

  private:
    // camera attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    // euler angles
    float m_yaw;
    float m_pitch;

    // camera options
    float m_aspect;
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;
    float m_near;
    float m_far;
};

} // namespace an::gfx

#endif // AN_GRAPHICS_CAMERA_H

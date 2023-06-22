#include <Graphics/Camera.h>
#include <algorithm>

namespace
{

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;
constexpr float ASPECT = 16.0f / 9.0f;
constexpr float CAMERA_NEAR = 0.1;
constexpr float CAMERA_FAR = 30;

} // namespace

using namespace an::gfx;

Camera::Camera(glm::vec3 position, glm::vec3 up)
    : m_position {position}
    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    , m_worldUp {up}
    , m_yaw {YAW}
    , m_pitch {PITCH}
    , m_aspect(ASPECT)
    , m_movementSpeed(SPEED)
    , m_mouseSensitivity(SENSITIVITY)
    , m_zoom(ZOOM)
    , m_near {CAMERA_NEAR}
    , m_far {CAMERA_FAR}
{
    updateCameraVectors();
}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::processKeyboard(Direction direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;

    switch(direction)
    {
        case an::gfx::Camera::Direction::FORWARD:
            m_position += m_front * velocity;
            break;
        case an::gfx::Camera::Direction::BACKWARD:
            m_position -= m_front * velocity;
            break;
        case an::gfx::Camera::Direction::LEFT:
            m_position -= m_right * velocity;
            break;
        case an::gfx::Camera::Direction::RIGHT:
            m_position += m_right * velocity;
            break;
        default:
            assert(false);
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if(constrainPitch)
    {
        m_pitch = std::clamp(m_pitch, -89.0f, 89.0f);
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    m_zoom -= yoffset;
    m_zoom = std::clamp(m_zoom, 1.0f, 45.0f);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front {
        cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
        sin(glm::radians(m_pitch)),
        sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))};
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

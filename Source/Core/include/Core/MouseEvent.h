#ifndef CORE_MOUSE_EVENT
#define CORE_MOUSE_EVENT

#include "Core/Event.h"

namespace an
{

class MouseMovedEvent final : public Event
{
  public:
    MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

    inline float getX() const { return m_mouseX; }
    inline float getY() const { return m_mouseY; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;

        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_mouseX;
    float m_mouseY;
};

class MouseScrollEvent final : public Event
{
  public:
    MouseScrollEvent(float x, float y) : m_xOffset(x), m_yOffset(y) {}

    inline float getXOffset() const { return m_xOffset; }
    inline float getYOffset() const { return m_yOffset; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseScrollEvent: " << m_xOffset << ", " << m_yOffset;

        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  private:
    float m_xOffset;
    float m_yOffset;
};

class MouseButtonEvent : public Event
{
  public:
    MouseButtonEvent(int button) : m_button(button) {}

    inline int getMouseButton() const { return m_button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

  protected:
    int m_button;
};

class MouseButtonPressedEvent final : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_button;

        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent final : public MouseButtonEvent
{
  public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_button;

        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

} // namespace an

#endif CORE_MOUSE_EVENT

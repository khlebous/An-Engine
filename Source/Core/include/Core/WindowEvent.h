#ifndef CORE_WINDOW_EVENT
#define CORE_WINDOW_EVENT

#include "Core/Event.h"

#include <sstream>

namespace an
{
class WindowResizeEvent final : public Event
{
  public:
    WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }

    std::string toString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_width << ", " << m_height;

        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

  private:
    unsigned int m_width;
    unsigned int m_height;
};

class WindowCloseEvent final : public Event
{
  public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
};

} // namespace an

#endif // CORE_WINDOW_EVENT

#ifndef CORE_KEY_EVENT
#define CORE_KEY_EVENT

#include "Core/Event.h"

#include <sstream>

namespace an
{
class KeyEvent : public Event
{
  public:
    inline int keyCode() const { return m_keyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

  protected:
    KeyEvent(int keyCode) : m_keyCode(keyCode) {}

    int m_keyCode;
};

class KeyPressedEvent final : public KeyEvent
{
  public:
    KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

    inline int repeatCount() const { return m_repeatCount; }

    std::string toString() const final
    {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";

        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

  private:
    int m_repeatCount;
};

class KeyReleasedEvent final : public KeyEvent
{
  public:
    KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

    std::string toString() const final
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_keyCode;

        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent final : public KeyEvent
{
  public:
    KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

    std::string toString() const final
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << m_keyCode;

        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};

} // namespace an

#endif // CORE_KEY_EVENT

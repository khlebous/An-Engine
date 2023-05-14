#ifndef CORE_EVENT
#define CORE_EVENT

#include <ostream>

namespace an
{

enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    KeyPressed,
    KeyReleased,
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

enum EventCategory
{
    None = 0,
    EventCategoryApplication = 0x01,
    EventCategoryInput = 0x02,
    EventCategoryKeyboard = 0x04,
    EventCategoryMouse = 0x08,
    EventCategoryButton = 0x10
};

#define EVENT_CLASS_TYPE(type)                                                                     \
    static EventType staticType() { return EventType::type; }                                      \
    virtual EventType eventType() const override { return staticType(); }                          \
    virtual const char *name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                                             \
    virtual int categoryFlags() const override { return category; }

class Event
{
    friend class EventDispatcher;

  public:
    virtual ~Event() = default;

    virtual EventType eventType() const = 0;
    virtual const char *name() const = 0;
    virtual int categoryFlags() const = 0;
    virtual std::string toString() const { return name(); }

    inline bool isInCategory(EventCategory category) { return categoryFlags() & category; }

    bool isHandled = false;
};

class EventDispatcher final
{
  public:
    EventDispatcher(Event &_event) : event(_event) {}

    template<typename T, typename F>
    bool dispatch(const F &func)
    {
        if(event.eventType() != T::staticType())
            return false;

        event.isHandled = func(static_cast<T &>(event));
        return true;
    }

  private:
    Event &event;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.toString();
}

} // namespace an

#endif // CORE_EVENT

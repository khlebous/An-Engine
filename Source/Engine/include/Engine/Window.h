#ifndef AN_ENGINE_WINDOW
#define AN_ENGINE_WINDOW

#include <functional>
#include <memory>
#include <string>

namespace an
{

class Event;

class GraphicsContext;

class Window
{
    struct Impl;
    using EventCallbackFn = std::function<void(Event &)>;

  public:
    Window(const std::string &name, unsigned int width = 1600, unsigned int height = 900);
    ~Window();

    unsigned int getWidth() const { return m_data.m_width; }
    unsigned int getHeight() const { return m_data.m_height; }

    void setVSync(bool enabled);
    bool isVSync() const;

    void onUpdate();

    void *getNativeWindow();
    void setEventCallback(const EventCallbackFn &callback) { m_data.m_eventCallback = callback; }

  private:
    void init();

  private:
    std::unique_ptr<Window::Impl> m_pImpl;
    std::unique_ptr<GraphicsContext> m_graphicsContext;

    struct WindowData
    {
        std::string m_name;
        unsigned int m_width = 0, m_height = 0;
        bool m_vSync = false;

        EventCallbackFn m_eventCallback;
    };
    WindowData m_data;
};

} // namespace an

#endif // AN_ENGINE_WINDOW
#ifndef AN_ENGINE_APPLICATION
#define AN_ENGINE_APPLICATION

#include "Engine/LayerStack.h"
#include "Engine/Window.h"

namespace an
{

class Event;
class ImguiLayer;
class WindowCloseEvent;
class WindowResizeEvent;

class Application
{
    class Impl;

  public:
    static Application &get() { return *m_instance; }

  public:
    Application();

    Window &getWindow() { return *m_window; }

    void run();
    void close();
    void onEvent(Event &event);

  protected:
    LayerStack m_layerStack;

  private:
    bool onWindowClose(WindowCloseEvent &event);
    bool onWindowResize(WindowResizeEvent &event);

    std::unique_ptr<Window> m_window;
    bool m_isMinimized = false;
    bool m_isRunning = true;
    double lastFrameTime = 0.0f;
    ImguiLayer *m_imguiOverlay;

    static Application *m_instance;
};

std::unique_ptr<Application> createApplication();

} // namespace an

#endif // AN_ENGINE_APPLICATION
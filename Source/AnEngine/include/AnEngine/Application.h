#ifndef AN_ENGINE_APPLICATION
#define AN_ENGINE_APPLICATION

#include "AnEngine/LayerStack.h"
#include "AnEngine/Window.h"

namespace an
{

class Application final
{
  public:
    static Application &get() { return *m_instance; }

  public:
    Application();

    Window &getWindow() { return *m_window; }

    void run();

  private:
    std::unique_ptr<Window> m_window;
    bool m_isRunning = true;
    LayerStack m_layerStack;

    static Application *m_instance;
};

Application *CreateApplication();

} // namespace an

#endif // AN_ENGINE_APPLICATION
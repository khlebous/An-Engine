#ifndef AN_ENGINE_WINDOW
#define AN_ENGINE_WINDOW

#include <GLFW/glfw3.h>

#include <string>
#include <memory>

namespace an
{

class GraphicsContext;

class Window
{
  public:
    Window(const std::string &name, unsigned int width = 1600, unsigned int height = 900);
    ~Window();

    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_heigth; }

    void setVSync(bool enabled);
    bool isVSync() const;

    void onUpdate();

  private:
    void init();

  private:
    GLFWwindow *m_glfwWindow;
    std::string m_name;
    bool m_vSync;
    unsigned int m_width;
    unsigned int m_heigth;

    std::unique_ptr<GraphicsContext> m_graphicsContext;
};

} // namespace an

#endif // AN_ENGINE_WINDOW
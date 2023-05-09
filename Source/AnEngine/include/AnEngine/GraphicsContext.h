#ifndef AN_ENGINE_GRAPHICS_CONTEXT
#define AN_ENGINE_GRAPHICS_CONTEXT

#include <GLFW/glfw3.h>

namespace an
{

class GraphicsContext
{
  public:
    virtual void init() = 0;
    virtual void swapBuffers() = 0;
};

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
class OpenGLContext final: public GraphicsContext
{
  public:
    OpenGLContext(GLFWwindow *window);

    void init() final;
    void swapBuffers() final;

  private:
    GLFWwindow *m_window;
};

} // namespace an

#endif // AN_ENGINE_GRAPHICS_CONTEXT

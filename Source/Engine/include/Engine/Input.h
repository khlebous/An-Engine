#ifndef AN_ENGINE_INPUT
#define AN_ENGINE_INPUT

#include <utility>

namespace an
{

class Input
{
  public:
    static bool isKeyPressed(int keycode);
    static bool isMouseButtonPressed(int button);

    static std::pair<double, double> getMousePosition();
    static float getMouseX();
    static float getMouseY();
};

} // namespace an

#endif // AN_ENGINE_INPUT

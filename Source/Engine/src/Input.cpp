#include "Engine/Input.h"

#include "Engine/Application.h"

#include <GLFW/glfw3.h>

using namespace an;

namespace
{

GLFWwindow *getWindow()
{
    return static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
}

} // namespace

//--------------------------------------------------------------------------------------------------
bool Input::isKeyPressed(int keycode)
{
    auto state = glfwGetKey(getWindow(), keycode);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

//--------------------------------------------------------------------------------------------------
bool Input::isMouseButtonPressed(int button)
{
    auto state = glfwGetKey(getWindow(), button);

    return state == GLFW_PRESS;
}

//--------------------------------------------------------------------------------------------------
std::pair<double, double> Input::getMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(getWindow(), &xpos, &ypos);

    return std::pair<double, double>(xpos, ypos);
}

//--------------------------------------------------------------------------------------------------
float Input::getMouseX()
{
    auto [xpos, ypos] = getMousePosition();

    return xpos;
}

//--------------------------------------------------------------------------------------------------
float Input::getMouseY()
{
    auto [xpos, ypos] = getMousePosition();

    return ypos;
}

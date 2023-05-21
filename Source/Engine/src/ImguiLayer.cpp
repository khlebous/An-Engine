#include "Engine/ImguiLayer.h"

#include "Engine/Application.h"

#include <Core/Event.h>
#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

namespace an
{

//--------------------------------------------------------------------------------------------------
void ImguiLayer::onAttach()
{
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    auto &app = Application::get();
    GLFWwindow *window = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

//--------------------------------------------------------------------------------------------------
void ImguiLayer::onDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

//--------------------------------------------------------------------------------------------------
void ImguiLayer::onImgui()
{
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

//--------------------------------------------------------------------------------------------------
void ImguiLayer::onEvent(Event &event)
{
    ImGuiIO &io = ImGui::GetIO();
    event.isHandled |= event.isInCategory(EventCategoryMouse) & io.WantCaptureMouse;
    event.isHandled |= event.isInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
}

//--------------------------------------------------------------------------------------------------
void ImguiLayer::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

//--------------------------------------------------------------------------------------------------
void ImguiLayer::end()
{
    ImGuiIO &io = ImGui::GetIO();
    Application &app = Application::get();
    io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

} // namespace an

#include "AnEngine/ImguiLayer.h"

#include "AnEngine/Application.h"

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

namespace an
{

//--------------------------------------------------------------------------------------------------
void an::ImguiLayer::onAttach()
{
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init("#version 430");
}

//--------------------------------------------------------------------------------------------------
void ImguiLayer::onUpdate()
{
    ImGuiIO &io = ImGui::GetIO();
    Application &app = Application::get();
    io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

    float currTime = (float)glfwGetTime();
    io.DeltaTime = time > 0.0f ? (currTime - time) : (1.0f / 60.0f);
    time = currTime;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    //ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//--------------------------------------------------------------------------------------------------
void ImguiLayer::onDetach() {}

} // namespace an

#include "imgui_layer.h"
#include "../core/Application.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Wolf {
namespace Layers {
    void ImGuiLayer::on_start()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        ImGui::StyleColorsDark();
        auto& app = Application::get();
        Unique<Window>& window = app->get_main_window();
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->get_native_ptr(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        capture_events = true;
        name = "ImGuiLayer";
    }

    void ImGuiLayer::on_end()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::on_update(const Time& delta)
    {
    }

    void ImGuiLayer::on_render()
    {
    }

    void ImGuiLayer::on_event(const Unique<Event>& event)
    {
        EventDispatcher dispatcher(event);
        ImGuiIO io = ImGui::GetIO();

        if (capture_events) {
            if (event->category & EventCategory::CategoryMouseButton)
                event->handled |= io.WantCaptureMouse;

            if (event->category & EventCategory::CategoryKeyboard)
                event->handled |= io.WantCaptureKeyboard;
        }
    }
    void ImGuiLayer::on_ui_render_start()
    {
        // Tell OpenGL a new frame is about to begin
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::on_ui_render_finish()
    {
        // Renders the ImGUI elements
        ImGuiIO& io = ImGui::GetIO();
        auto& app = Application::get();
        io.DisplaySize = ImVec2(
            app->get_main_window()->get_width(),
            app->get_main_window()->get_height());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(current_context);
        }
    }

}
}

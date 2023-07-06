#ifndef WOLF_TEST_PERFORMANCE_DISPLAY_H
#define WOLF_TEST_PERFORMANCE_DISPLAY_H
#include "WEngine.h"
#include <imgui/imgui.h>


namespace Tests
{
    class PerformanceDisplayLayer : public Wolf::Layer
    {

        void on_ui_render_start()
        {
            ImGui::Begin("Status");
            float render_time = Wolf::Application::get()->get_render_time().seconds();
            float update_time = Wolf::Application::get()->get_update_time().seconds();
            ImGui::Text(("Render time: " + std::to_string(render_time)).c_str());
            ImGui::Text(("Update time: " + std::to_string(update_time)).c_str());
            ImGui::End();
        }
    };
}


#endif
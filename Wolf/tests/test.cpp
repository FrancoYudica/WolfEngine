
#include <iostream>

#include "WEngine.h"
#include "assets/bitmap_load_test.hpp"
#include "assets/bitmap_save_test.hpp"
#include "imgui_tests/imgui_docking.hpp"
#include "performance_display.hpp"
#include "renderer/batch_renderer_test.hpp"
#include "renderer/sprite_rendering_test.hpp"
#include "renderer/texture_test.hpp"
#include "renderer/sprite_animation_test.hpp"
#include <memory>

using namespace Wolf;

int main()
{
    bool success = Wolf::init(Wolf::Window::Configuration());
    if (!success)
        return -1;

    // CLient layer
    auto& app = Wolf::Application::get();
    Shared<Wolf::Layer> performance_layer = std::make_shared<Tests::PerformanceDisplayLayer>();
    app->add_layer(performance_layer);

    Shared<Wolf::Layer> test_layer = std::make_shared<Tests::Renderer::SpriteAnimationLayer>();
    app->add_layer(test_layer);
    app->run();
    return 0;
}
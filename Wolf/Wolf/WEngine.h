
#ifndef __WOLF_ENGINE_INCLUDE__
#define __WOLF_ENGINE_INCLUDE__

#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Core includes
#include "core/Application.h"
#include "core/Event.h"
#include "core/Layer.h"
#include "core/Time.h"
#include "core/Window.h"
#include "core/wolf_types.h"

// ImGui layer
#include "imgui_layer/imgui_layer.h"

// Rendering
#include "rendering/BitMap.h"
#include "rendering/Buffer.h"
#include "rendering/Camera.h"
#include "rendering/RenderCommand.h"
#include "rendering/Renderer.h"
#include "rendering/ShaderProgram.h"
#include "rendering/Texture.h"
#include "rendering/VertexArray.h"

// Numerical
#include "numerical/Random.h"
#include "numerical/numerical.h"
#include "numerical/Bounds.h"

// Utils
#include "utils/File.h"
#include "utils/PathManager.h"

// Input
#include "input/input.h"
#include "input/input_transform.h"
#include "input/Cursor.h"

// Assets
#include "assets/assets.h"

// Animation
#include "animation/SpriteAnimation.h"

namespace Wolf {
static bool init(const Window::Configuration& window_config)
{
    std::cout << "Welcome to wolf engine v" << WOLF_ENGINE_VERSION << std::endl;
    auto& app = Application::get();
    bool success = app->initialize(window_config);
    if (!success) {
        std::cout << "Application init fail" << std::endl;
        return false;
    }

    Rendering::Renderer2D::init();

    // If imgui is used
    Shared<Layer> imguiLayer = std::make_shared<Layers::ImGuiLayer>();
    app->set_imgui_layer(imguiLayer);
    return true;
}
}

#endif
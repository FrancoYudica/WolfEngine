#pragma once
#ifndef WOLF_ENGINE_INCLUDE_H
#define WOLF_ENGINE_INCLUDE_H

#include <glm/glm.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include <string>

// Core includes
#include "core/wolf_types.h"
#include "core/Application.h"
#include "core/Event.h"
#include "core/Time.h"
#include "core/Layer.h"
#include "core/Window.h"

// ImGui layer
#include "imgui_layer/imgui_layer.h"

// Rendering
#include "rendering/ShaderProgram.h"
#include "rendering/Buffer.h"
#include "rendering/VertexArray.h"
#include "rendering/Renderer.h"
#include "rendering/RenderCommand.h"
#include "rendering/Camera.h"
#include "rendering/BitMap.h"
#include "rendering/Texture.h"

// Numerical
#include "numerical/Random.h"
#include "numerical/numerical.h"

// Utils
#include "utils/File.h"
#include "utils/PathManager.h"

// Input
#include "input/input_transform.h"
#include "input/input.h"


namespace Wolf
{
    static bool init()
    {
        std::cout << "Welcome to wolf engine v" << WOLF_ENGINE_VERSION << std::endl;
        auto& app = Application::get();
        bool success = app->initialize(Window::Configuration());
        if (!success)
        {
            std::cout << "Application init fail" << std::endl;
            return  false;
        }

        Rendering::Renderer2D::init();

        // If imgui is used
        Shared<Layer> imguiLayer = std::make_shared<Layers::ImGuiLayer>();
        app->set_imgui_layer(imguiLayer);
        return true;
    }
}

#endif
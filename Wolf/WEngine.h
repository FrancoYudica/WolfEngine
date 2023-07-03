#pragma once
#ifndef WOLF_ENGINE_INCLUDE_H
#define WOLF_ENGINE_INCLUDE_H

#include <glm/glm.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include <string>

// Core includes
#include "Wolf/core/wolf_types.h"
#include "Wolf/core/Application.h"
#include "Wolf/core/Event.h"
#include "Wolf/core/Time.h"
#include "Wolf/core/Layer.h"
#include "Wolf/core/Window.h"

// ImGui layer
#include "Wolf/imgui_layer/imgui_layer.h"

// Rendering
#include "Wolf/rendering/ShaderProgram.h"
#include "Wolf/rendering/Buffer.h"
#include "Wolf/rendering/VertexArray.h"
#include "Wolf/rendering/Renderer.h"
#include "Wolf/rendering/RenderCommand.h"
#include "Wolf/rendering/Camera.h"

// Numerical
#include "Wolf/numerical/Random.h"
#include "Wolf/numerical/numerical.h"

// Utils
#include "Wolf/utils/File.h"
#include "Wolf/utils/PathManager.h"

// Input
#include "Wolf/input/input_transform.h"
#include "Wolf/input/input.h"


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
        // If imgui is used
        Shared<Layer> imguiLayer = std::make_shared<Layers::ImGuiLayer>();
        app->set_imgui_layer(imguiLayer);
        return true;
    }
}

#endif
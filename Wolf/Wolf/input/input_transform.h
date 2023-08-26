#pragma once
#ifndef __WOLF_INPUT_TRANSFORM__
#define __WOLF_INPUT_TRANSFORM__
#include "../rendering/Camera.h"
#include <glm/glm.hpp>

namespace Wolf {
namespace Input {

    glm::vec2 screen_to_world_coord(const Rendering::Camera& camera, glm::vec2 local);
    glm::vec2 world_to_screen_coord(const Rendering::Camera& camera, glm::vec2 world);
}
}

#endif
#include "Cursor.h"
#include "../core/Application.h"
#include <GLFW/glfw3.h>

namespace Wolf {
namespace Cursor {
    void set_mode(CursorMode mode)
    {
        auto& window = Application::get()->get_main_window();
        constexpr const uint32_t base_cursor_mode = 0x00034001;
        glfwSetInputMode(
            static_cast<GLFWwindow*>(window->get_native_ptr()),
            GLFW_CURSOR,
            static_cast<uint32_t>(mode) + base_cursor_mode);
    }
}
}
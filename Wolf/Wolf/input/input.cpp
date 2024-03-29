#include "input.h"
#include "../core/Application.h"
#include <GLFW/glfw3.h>

namespace Wolf {
namespace Input {

    /// @brief Returns mouse position in [0, width] and [0, height] ranges
    glm::vec2 get_pixel_mouse_pos()
    {
        double x, y;
        Unique<Wolf::Window>& window = Application::get()->get_main_window();
        glfwGetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), &x, &y);
        return { x, y };
    }

    /// @brief Sets mouse position in [0, width] and [0, height] ranges
    void set_pixel_mouse_pos(glm::vec2 pos)
    {
        Unique<Wolf::Window>& window = Application::get()->get_main_window();
        glfwSetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), pos.x, pos.y);
    }

    /// @brief Returns mouse position in [-1, 1] cartesian range
    glm::vec2 get_mouse_pos_norm()
    {
        double x_pixel, y_pixel;
        Unique<Wolf::Window>& window = Application::get()->get_main_window();
        glfwGetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), &x_pixel, &y_pixel);

        float norm_x = x_pixel / static_cast<double>(window->get_width());
        float norm_y = y_pixel / static_cast<double>(window->get_height());

        return { (norm_x - 0.5) * 2, ((1 - norm_y) - 0.5) * 2 };
    }

    /// @brief Returns mouse position.
    /// X axis ranges in [-aspect_ratio, aspect_ratio]
    /// Y axis ranges in [-1.0, 1.0]
    glm::vec2 get_mouse_pos()
    {

        double x_pixel, y_pixel;
        Unique<Wolf::Window>& window = Application::get()->get_main_window();
        glfwGetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), &x_pixel, &y_pixel);
        float aspect_ratio = static_cast<float>(window->get_width()) / static_cast<float>(window->get_height());
        float norm_x = x_pixel / static_cast<double>(window->get_width());
        float norm_y = y_pixel / static_cast<double>(window->get_height());

        return { (norm_x - 0.5) * 2 * aspect_ratio, ((1 - norm_y) - 0.5) * 2 };
    }
    void set_mouse_pos(glm::vec2 pos)
    {
        Unique<Wolf::Window>& window = Application::get()->get_main_window();
        float aspect_ratio = static_cast<float>(window->get_width()) / static_cast<float>(window->get_height());
        uint32_t x = 0.5f * (1.0f + pos.x / aspect_ratio) * window->get_width();
        uint32_t y = 0.5f * (1.0f - pos.y) * window->get_height();

        glfwSetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), x, y);
    }

    void set_mouse_pos_norm(glm::vec2 pos)
    {
        Unique<Wolf::Window>& window = Application::get()->get_main_window();
        uint32_t x = 0.5f * (1.0f + pos.x) * window->get_width();
        uint32_t y = 0.5f * (1.0f - pos.y) * window->get_height();
        glfwSetCursorPos(static_cast<GLFWwindow*>(window->get_native_ptr()), x, y);
    }

    bool is_key_down(KeyCode code)
    {
        Unique<Wolf::Window>& window = Application::get()->get_main_window();

        int state = glfwGetKey(static_cast<GLFWwindow*>(window->get_native_ptr()), code);
        return state == GLFW_PRESS;
    }

    bool is_button_down(MouseButton code)
    {
        Unique<Wolf::Window>& window = Application::get()->get_main_window();
        int state = glfwGetMouseButton(static_cast<GLFWwindow*>(window->get_native_ptr()), code);
        return state == GLFW_PRESS;
    }

}
}

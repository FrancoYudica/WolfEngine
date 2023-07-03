#include "OpenGLContext.h"
#include "GLBuffer.h"
#include "GLShaderProgram.h"
#include "GLVertexArray.h"
#include <memory>
#include <glad/glad.h>
#include "core/Window.h"
#include "core/wolf_types.h"
#include "rendering/RenderCommand.h"
#include <GLFW/glfw3.h>


using namespace Wolf;
using namespace Wolf::Rendering;
using namespace Wolf::Rendering::GL;

// GRAPHICS CONTEXT
Shared<GraphicsContext> GraphicsContext::create(Unique<Window>& window)
{
    return std::make_shared<GLGraphicsContext>(window->get_native_ptr());
}

void GLGraphicsContext::init()
{
    int success = gladLoadGL();
    if (success == 0)
        std::cout << "Unable to load glad" << std::endl;
}

void GLGraphicsContext::on_viewport_resize(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}

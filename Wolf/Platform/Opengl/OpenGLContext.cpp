#include "OpenGLContext.h"
#include "GLBuffer.h"
#include "GLShaderProgram.h"
#include "GLVertexArray.h"
#include <memory>
#include <glad/glad.h>
#include "core/Window.h"
#include "rendering/RenderCommand.h"
#include <GLFW/glfw3.h>


using namespace Wolf;
using namespace Wolf::Rendering;
using namespace Wolf::Rendering::GL;

// GRAPHICS CONTEXT
std::shared_ptr<GraphicsContext> GraphicsContext::Create(const Wolf::Window& window)
{
    return std::make_shared<GLGraphicsContext>(window.GetNativePtr());
}

void GLGraphicsContext::Init()
{
    int sucess = gladLoadGL();
    if (sucess == 0)
        std::cout << "Unable to load glad" << std::endl;
}
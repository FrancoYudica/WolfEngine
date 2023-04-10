#include "OpenGLContext.h"
#include "GLBuffer.h"
#include "GLShaderProgram.h"
#include "GLVertexArray.h"
#include <memory>
#include <glad/glad.h>
#include "core/Window.h"
#include <GLFW/glfw3.h>

using namespace Wolf;
using namespace Wolf::Rendering;

std::shared_ptr<GraphicsContext> GraphicsContext::Create(const Wolf::Window& window)
{
    return std::make_shared<GL::GLGraphicsContext>(window.GetNativePtr());
}


void GL::GLGraphicsContext::Init()
{
    int sucess = gladLoadGL();
    if (sucess == 0)
        std::cout << "Unable to load glad" << std::endl;
}


void GL::GLGraphicsContext::SwapBuffers()
{
    glfwSwapBuffers((GLFWwindow*)_glfwWindow);
}

// Links the definitions of all the other RENDERING Static functions
std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, unsigned int size)
{
    // Size is the amount of bytes of the array
    return std::make_shared<GL::GLVertexBuffer>(data, size);
}

std::shared_ptr<VertexBuffer> VertexBuffer::CreateEmpty(unsigned int size)
{
    return std::make_shared<GL::GLVertexBuffer>(size);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const unsigned int* data, unsigned int count)
{
    // Count is the length of the array
    return std::make_shared<GL::GLIndexBuffer>(data, count);
}

std::shared_ptr<VertexArray> VertexArray::Create()
{
    return std::make_shared<GL::GLVertexArray>();
}

std::shared_ptr<ShaderProgram> ShaderProgram::Create(const char* vertex_src, const char* fragment_src)
{
    return std::make_shared<GL::GLShaderProgram>(vertex_src, fragment_src);
}

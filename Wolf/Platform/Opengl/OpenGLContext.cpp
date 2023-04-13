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

// GRAPHICS CONTEXT
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

// Links the definitions of all the other RENDERING Static functions
std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, unsigned int size)
{
    // Size is the amount of bytes of the array
    return std::make_shared<GL::GLVertexBuffer>(data, size);
}

std::shared_ptr<VertexBuffer> VertexBuffer::Allocate(unsigned int size)
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


static float _CommandClearColor[] = {0, 0, 0, 1};
// Links the definitions for the render commands
void RenderCommand::SetClearColor(float r, float g, float b, float a)
{
    _CommandClearColor[0] = r;
    _CommandClearColor[1] = g;
    _CommandClearColor[2] = b;
    _CommandClearColor[3] = a;
}

void RenderCommand::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);   
}

void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vao, int count)
{
    auto ibo = vao->get_index_buffer();
    ibo->bind();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}


#include <glad/glad.h>
#include "../WEngine.h"

using namespace Wolf::Rendering;


// Links the definitions for the render commands
void RenderCommand::SetClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
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
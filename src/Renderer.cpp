#include "Renderer.h"

#include <iostream>
#include <format>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* filename, int line) {
    while (GLenum error = glGetError()) {
        std::cout << std::format("[OpenGLError] ({}): function: {} file: {} line: {}\n", error, function, filename, line);
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    
    GLCALL(glDrawElements(GL_TRIANGLES, ib.m_count(), GL_UNSIGNED_INT, nullptr))
}

void Renderer::Clear() const {
    GLCALL(glClear(GL_COLOR_BUFFER_BIT))
}


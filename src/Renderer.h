﻿#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
x;\
ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GlLogCall(const char* function, const char* filename, int line);

class Renderer {
public:
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};
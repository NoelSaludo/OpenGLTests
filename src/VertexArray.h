#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);

    [[nodiscard]] unsigned int getRendererID() const { return m_RendererID; }
private:
    unsigned int m_RendererID;
};

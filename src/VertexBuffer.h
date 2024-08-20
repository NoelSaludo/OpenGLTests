#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;


    [[nodiscard]] unsigned int getRendererID() const { return m_RendererID; }

private:
    unsigned int m_RendererID;
};

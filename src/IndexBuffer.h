﻿#pragma once


class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    [[nodiscard]] unsigned int m_count() const {
        return m_Count;
    }

    [[nodiscard]] unsigned int getRendererID(){
        return m_RendererID;
    }

private:
    unsigned int m_RendererID;
    unsigned int m_Count;
};

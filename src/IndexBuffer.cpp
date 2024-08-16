﻿#include "IndexBuffer.h"

#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    GLCALL(glGenBuffers(1, &this->m_RendererID))
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID))
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW))
}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &this->m_RendererID))
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_RendererID))
}
                                                  
void IndexBuffer::UnBind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}

#include "VertexArray.h"
#include "renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
    GLCALL(glGenVertexArrays(1, &this->m_RendererID));
}

VertexArray::~VertexArray() {
    GLCALL(glDeleteVertexArrays(1, &this->m_RendererID));
}

void VertexArray::Bind() const {
    GLCALL(glBindVertexArray(m_RendererID))
}

void VertexArray::Unbind() const {
    GLCALL(glBindVertexArray(0))
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbl) {
    this->Bind();
    vb.Bind();
    const auto &elements = vbl.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++) {
        const auto element = elements[i];
        GLCALL(glEnableVertexAttribArray(i))
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.isNormalized, vbl.GetStride(), (const void*)offset))
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

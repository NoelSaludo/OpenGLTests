#pragma once

#include <memory>
#include "Test.h"

#include "renderer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

#include <memory>

namespace test {
class ObjectColorTest : public Test{
public:
    ObjectColorTest();
    ~ObjectColorTest() override;

    void OnRender() override;
    void OnUpdate(float deltaTime) override;
    void OnImGuiRender() override;

private:
    float m_Color[4];
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<VertexBuffer> m_VB;
    std::unique_ptr<Renderer> m_Renderer;
};}

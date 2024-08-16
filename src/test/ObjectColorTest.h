#pragma once
#include "Test.h"

#include "../renderer.h"
#include "../Shader.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"

namespace test {
class ObjectColorTest : public Test{
public:
    ObjectColorTest();
    ~ObjectColorTest() override;

    void OnRender() override;
    void OnUpdate(Shader& shader);
    void OnImGuiRender() override;

private:
    float m_Color[4];
};}

#include "ObjectColorTest.h"

#include "imgui/imgui.h"


test::ObjectColorTest::ObjectColorTest() : m_Color{1.0,1.0,1.0,1.0}{
}

test::ObjectColorTest::~ObjectColorTest() {
}

void test::ObjectColorTest::OnRender() {
}

void test::ObjectColorTest::OnUpdate(Shader& shader) {
    shader.Bind();
    shader.SetUniform4f("u_Color", this->m_Color[0], this->m_Color[1], this->m_Color[2], this->m_Color[3]);
}

void test::ObjectColorTest::OnImGuiRender() {
    ImGui::ColorEdit4("Object Color", this->m_Color);
}

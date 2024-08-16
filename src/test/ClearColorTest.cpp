#include "ClearColorTest.h"

#include "../renderer.h"
#include "imgui/imgui.h"

test::ClearColorTest::ClearColorTest() : m_Color{1.0,1.0,1.0,1.0} {
}

test::ClearColorTest::~ClearColorTest() {
}

void test::ClearColorTest::OnRender() {
    GLCALL(glClearColor(m_Color[0],m_Color[1],m_Color[2],m_Color[3]))
    GLCALL(glClear(GL_COLOR_BUFFER_BIT))
}

void test::ClearColorTest::OnImGuiRender() {
    ImGui::ColorEdit4("color",m_Color);
}


void test::ClearColorTest::OnUpdate(float deltaTime) {
    
}

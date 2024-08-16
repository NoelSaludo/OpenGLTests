#include "Test.h"

#include "imgui/imgui.h"

test::TestMenu::TestMenu(Test*& currentTest)
    : m_CurrentTest(currentTest){
}

test::TestMenu::~TestMenu() {
}

void test::TestMenu::OnImGuiRender() {
    for(const auto& test : this->m_Tests) {
        if(ImGui::Button(test.first.c_str())) {
            m_CurrentTest = test.second();
        }
    }
}




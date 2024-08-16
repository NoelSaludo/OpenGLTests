#include "ObjectColorTest.h"

#include "imgui/imgui.h"
#include "VertexBufferLayout.h"

test::ObjectColorTest::ObjectColorTest()
    : m_Color{1.0,1.0,1.0,1.0}{
    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f, 0.5f
    };
    unsigned int indices[] = {
            0,1,2
    };

    m_VAO = std::make_unique<VertexArray>();
    m_VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VB, layout);

    m_IBO = std::make_unique<IndexBuffer>(indices,3);

    m_Shader = std::make_unique<Shader>("../res/shaders/Color.shader");
    m_Shader->Bind();

    m_Renderer = std::make_unique<Renderer>();
}

test::ObjectColorTest::~ObjectColorTest() {
}

void test::ObjectColorTest::OnRender() {
    m_Renderer->Draw(*this->m_VAO,*this->m_IBO,*this->m_Shader);
}

void test::ObjectColorTest::OnUpdate(float deltaTime) {
    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", this->m_Color[0],this->m_Color[1],this->m_Color[2],this->m_Color[3]);
}

void test::ObjectColorTest::OnImGuiRender() {
    ImGui::ColorEdit4("Object Color", this->m_Color);
}

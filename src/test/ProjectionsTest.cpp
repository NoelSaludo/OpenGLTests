#include "ProjectionsTest.h"
#include "VertexBufferLayout.h"
#include "imgui/imgui.h"

test::ProjectionsTest::ProjectionsTest()
    : m_Proj(glm::ortho(0.0f,1600.0f,0.0f,1080.0f,-1.0f,1.0f)),
      m_ViewVec3(0.0f,0.0f,0.0f),
      m_ModelVec3(0.0f,0.0f,0.0f){
    float vertices[] = {
            0.0f, 0.0f,
            500.0f, 0.0f,
            250.0f, 500.0f
    };
    unsigned int indices[] = {
            0,1,2
    };

    this->m_VAO = std::make_unique<VertexArray>();
    this->m_VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    this->m_VAO->AddBuffer(*this->m_VB, layout);

    this->m_IBO = std::make_unique<IndexBuffer>(indices, 3);

    this->m_Shader = std::make_unique<Shader>("../res/shaders/Projection.shader");
    this->m_Shader->Bind();

    this->m_Renderer = std::make_unique<Renderer>();
}

test::ProjectionsTest::~ProjectionsTest() {

}

void test::ProjectionsTest::OnUpdate(float deltaTime) {
    m_View = glm::translate(glm::mat4(1.0f),m_ViewVec3);
    m_Model = glm::translate(glm::mat4(1.0f),m_ModelVec3);
    this->m_MVP = this->m_Proj * this->m_View * this->m_Model;
    this->m_Shader->Bind();
    this->m_Shader->SetMat4f("u_MVP", this->m_MVP);
    this->m_Shader->Bind();
    this->m_Shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
}

void test::ProjectionsTest::OnRender() {
    this->m_Renderer->Draw(*this->m_VAO, *this->m_IBO, *this->m_Shader);
}

void test::ProjectionsTest::OnImGuiRender() {
    ImGui::SliderFloat3("View",&this->m_ViewVec3.x,-540.0f,540.0f);
    ImGui::SliderFloat3("Model",&this->m_ModelVec3.x,-540.0f,540.0f);
}

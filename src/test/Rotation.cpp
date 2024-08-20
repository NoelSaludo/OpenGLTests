//
// Created by noels on 20/08/2024.
//
#include "Rotation.h"
#include "VertexBufferLayout.h"
#include "imgui/imgui.h"

test::Rotation::Rotation()
    : m_Proj(glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 100.0f)),
      m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3))),
      m_rx(0.0f) , m_ry(0.0f), m_rz(0.0f) {
    float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
    };

    GLCALL(glEnable(GL_BLEND))
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    this->m_VAO = std::make_unique<VertexArray>();
    this->m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 5 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    this->m_VAO->AddBuffer(*this->m_VBO, layout);

    this->m_IBO = std::make_unique<IndexBuffer>(indices, 6);

    this->m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");
    this->m_Shader->Bind();
    this->m_Texture = std::make_unique<Texture>("../res/textures/brick.png");
    this->m_Texture->Bind();
    this->m_Shader->SetUniform1i("u_Texture", 0);

    this->m_Renderer = std::make_unique<Renderer>();
}

test::Rotation::~Rotation() {}

void test::Rotation::OnUpdate(float deltaTime) {
    glm::mat4 modelx = glm::rotate(glm::mat4(1.0f), glm::radians(m_rx), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 modely = glm::rotate(glm::mat4(1.0f), glm::radians(m_ry), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 modelz = glm::rotate(glm::mat4(1.0f), glm::radians(m_rz), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 mvp = this->m_Proj * this->m_View * (modelx * modely * modelz);
    this->m_Shader->Bind();
    this->m_Shader->SetMat4f("u_MVP", mvp);
    this->m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
}

void test::Rotation::OnRender() {
    this->m_Renderer->Draw(*this->m_VAO, *this->m_IBO, *this->m_Shader);
}

void test::Rotation::OnImGuiRender() {
    ImGui::SliderFloat("Rotation x", &m_rx, 0.0f, 360.0f);
    ImGui::SliderFloat("Rotation y", &m_ry, 0.0f, 360.0f);
    ImGui::SliderFloat("Rotation z", &m_rz, 0.0f, 360.0f);
}
//
// Created by noels on 23/08/2024.
//

#include "ThirdDimTest.h"
#include "VertexBufferLayout.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"

test::ThirdDimTest::ThirdDimTest()
    : m_Proj(glm::perspective(glm::radians(45.0f), 960.0f/540.0f, 0.1f, 100.0f)){
    float vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    };

    glEnable(GL_DEPTH_TEST);

    m_VAO = std::make_unique<VertexArray>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VertexBuffer, layout);

    m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");
    m_Shader->Bind();
    m_Texture = std::make_unique<Texture>("../res/textures/brick.png");
    m_Texture->Bind();

    m_Shader->SetUniform1i("u_Texture", 0);

    m_Renderer = std::make_unique<Renderer>();
}

test::ThirdDimTest::~ThirdDimTest() = default;

void test::ThirdDimTest::OnUpdate(float deltaTime) {
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime()*glm::radians(55.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    glm::mat4 mvp = m_Proj * view * model;
    m_Shader->Bind();
    m_Shader->SetMat4f("u_MVP", mvp);
    m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
}

void test::ThirdDimTest::OnRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Bind();
    m_VAO->Bind();

    GLCALL(glDrawArrays(GL_TRIANGLES, 0, 36));
}

void test::ThirdDimTest::OnImGuiRender() {
    ImGui::Text("Third Dimension Test");
}
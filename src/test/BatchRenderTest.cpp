//
// Created by noels on 17/08/2024.
//

#include <iostream>
#include "BatchRenderTest.h"
#include "VertexBufferLayout.h"

#include "imgui/imgui.h"

namespace test {
    BatchRenderTest::BatchRenderTest()
    : m_Proj(glm::ortho(0.0f,960.0f,0.0f,540.0f,-1.0f,1.0f)),
      m_Model(glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,0.0f,0.0f))),
      m_ViewTranslation(0.0f,0.0f,0.0f){
        float vertices[] = {
                200.0f, 200.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                300.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                300.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
                200.0f, 300.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

                400.0f, 200.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                500.0f, 200.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
                500.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                400.0f, 300.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,

        };

        unsigned int indices[] ={
                0,1,2,
                2, 3, 0,
                4, 5, 6,
                6, 7, 4
        };

        m_VAO = std::make_unique<VertexArray>();
        m_VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(1);
        m_VAO->AddBuffer(*m_VB, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 12);

        m_Shader = std::make_unique<Shader>("../res/shaders/Batch.shader");
        m_Shader->Bind();

        m_Texture1 = std::make_unique<Texture>("../res/textures/brick.png");
        m_Texture1->Bind();

        m_Texture2 = std::make_unique<Texture>("../res/textures/wood.jpg");
        m_Texture2->Bind(1);

        m_Renderer = std::make_unique<Renderer>();

    }

    BatchRenderTest::~BatchRenderTest() {}

    void BatchRenderTest::OnUpdate(float deltaTime) {
        m_View = glm::translate(glm::mat4(1.0f),m_ViewTranslation);
        glm::mat4 mvp = m_Proj*m_View*m_Model;

        m_Shader->Bind();
        m_Shader->SetMat4f("u_MVP", mvp);

        m_Shader->Bind();
        glBindTextureUnit(0, m_Texture1->getMRendererId());
        glBindTextureUnit(1, m_Texture2->getMRendererId());

        m_Shader->Bind();
        auto location = glGetUniformLocation(m_Shader->getMRendererId(), "u_Textures");
        int samplers[2] = {0,1};
        glUniform1iv(location, 2, samplers);
    }

    void BatchRenderTest::OnRender() {
        m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader);
    }

    void BatchRenderTest::OnImGuiRender() {
        ImGui::SliderFloat3("view", &m_ViewTranslation.x, -540.0f, 960.0f);
    }
} // test
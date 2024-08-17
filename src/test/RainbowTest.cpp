//
// Created by noels on 17/08/2024.
//

#include "RainbowTest.h"

#include "VertexBufferLayout.h"

namespace test {
    RainbowTest::RainbowTest() {
        float vertices[] = {
                -1.0f,-1.0f, 1.0f, 0.0f, 0.0f,
                1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
                1.0f,1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f,1.0f, 1.0f, 1.0f, 0.0f,
                0.0f,0.0f, 1.0f, 1.0f, 1.0f,
        };

        unsigned int indices[] = {
                0, 1, 4,
                4, 3, 2,
                0,4,3,
                1,4,2
        };

        this->m_VAO = std::make_unique<VertexArray>();
        this->m_VB = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(3);
        this->m_VAO->AddBuffer(*this->m_VB, layout);

        this->m_IBO = std::make_unique<IndexBuffer>(indices, 12);

        this->m_Shader = std::make_unique<Shader>("../res/shaders/Rainbow.shader");
        this->m_Shader->Bind();

        this->m_Renderer = std::make_unique<Renderer>();
    }

    RainbowTest::~RainbowTest() {}

    void RainbowTest::OnUpdate(float deltaTime) {
        Test::OnUpdate(deltaTime);
    }

    void RainbowTest::OnRender() {
        this->m_Renderer->Draw(*this->m_VAO, *this->m_IBO, *this->m_Shader);
    }

    void RainbowTest::OnImGuiRender() {
        Test::OnImGuiRender();
    }
} // test
#pragma once

#include "Test.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test{
    class TexTest : public Test {
    public:
        TexTest();
        ~TexTest();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<Renderer> m_Renderer;

        glm::mat4 m_Proj, m_View, m_Model;
        glm::vec3 m_TranslationView, m_TranslationModel;

        float m_Color[4];
    };

}

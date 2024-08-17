#pragma once
#include "Test.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test {
    class ProjectionsTest : public Test {
    public:
        ProjectionsTest();
        ~ProjectionsTest() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        glm::mat4 m_Proj;
        glm::mat4 m_View;
        glm::mat4 m_Model;
        glm::mat4 m_MVP;

        glm::vec3 m_ViewVec3;
        glm::vec3 m_ModelVec3;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VB;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Renderer> m_Renderer;
    };
}

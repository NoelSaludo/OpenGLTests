//
// Created by noels on 17/08/2024.
//

#ifndef OPENGLAPP_BATCHRENDERTEST_H
#define OPENGLAPP_BATCHRENDERTEST_H

#include "Test.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

namespace test {

    class BatchRenderTest : public Test {
    public:
        BatchRenderTest();

        ~BatchRenderTest() override;

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;
    private:
        std::unique_ptr<Renderer> m_Renderer;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<VertexBuffer> m_VB;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture1;
        std::unique_ptr<Texture> m_Texture2;

        glm::mat4 m_Proj, m_View, m_Model;
        glm::vec3 m_ViewTranslation;
    };

} // test

#endif //OPENGLAPP_BATCHRENDERTEST_H

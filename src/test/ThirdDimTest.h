//
// Created by noels on 23/08/2024.
//

#ifndef OPENGLAPP_THIRDDIMTEST_H
#define OPENGLAPP_THIRDDIMTEST_H

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace test {
    class ThirdDimTest : public Test {
    public:
        ThirdDimTest();

        ~ThirdDimTest() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<Renderer> m_Renderer;

        glm::mat4 m_Proj;
    };
}


#endif //OPENGLAPP_THIRDDIMTEST_H

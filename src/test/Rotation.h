//
// Created by noels on 20/08/2024.
//

#ifndef OPENGLAPP_ROTATION_H
#define OPENGLAPP_ROTATION_H

#include "Test.h"

#include "renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace test {
    class Rotation : public Test {
    public:
        Rotation();

        ~Rotation() override;

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
       float m_rx, m_ry, m_rz;
    };
}

#endif //OPENGLAPP_ROTATION_H

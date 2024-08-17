//
// Created by noels on 17/08/2024.
//

#ifndef OPENGLAPP_RAINBOWTEST_H
#define OPENGLAPP_RAINBOWTEST_H

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

#include <memory>

namespace test {

    class RainbowTest : public Test {
    public:
        RainbowTest();

        ~RainbowTest() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VB;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Renderer> m_Renderer;

    };

} // test

#endif //OPENGLAPP_RAINBOWTEST_H

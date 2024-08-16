#include "TexTest.h"
#include "VertexBufferLayout.h"
#include "imgui/imgui.h"

test::TexTest::TexTest()
: m_Color{1.0f, 1.0f, 1.0f, 1.0f},
  m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
  m_TranslationView(0.0f,0.0f,0.0f),
  m_TranslationModel(0.0f,0.0f,0.0f) {
    float positions[] = {
            0.0f, 0.0f, 0.0f, 0.0f,
             400.0f, 0.0f, 1.0f, 0.0f,
             400.0f,  400.0f, 1.0f, 1.0f,
            0.0f,  400.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    GLCALL(glEnable(GL_BLEND))
    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

    this->m_VAO = std::make_unique<VertexArray>();
    this->m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    this->m_VAO->AddBuffer(*this->m_VBO, layout);

    this->m_IBO = std::make_unique<IndexBuffer>(indices, 6);

    this->m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");
    this->m_Shader->Bind();
    this->m_Texture = std::make_unique<Texture>("../res/textures/jr.jpg");
    this->m_Texture->Bind();
    this->m_Shader->SetUniform1i("u_Texture", 0);

    this->m_Renderer = std::make_unique<Renderer>();
}

test::TexTest::~TexTest() {

}

void test::TexTest::OnUpdate(float deltaTime) {
    this->m_View = glm::translate(glm::mat4(1.0f), this->m_TranslationView);
    this->m_Model = glm::translate(glm::mat4(1.0f), this->m_TranslationModel);
    glm::mat4 mvp = this->m_Proj * this->m_View * this->m_Model;
    this->m_Shader->Bind();
    this->m_Shader->SetUniform4f("u_Color", this->m_Color[0], this->m_Color[1], this->m_Color[2], this->m_Color[3]);
    this->m_Shader->SetMat4f("u_MVP", mvp);
}

void test::TexTest::OnRender() {
    this->m_Renderer->Draw(*this->m_VAO, *this->m_IBO, *this->m_Shader);
}

void test::TexTest::OnImGuiRender() {
    ImGui::ColorEdit4("Square Color", this->m_Color);
    ImGui::SliderFloat3("View Translation", &this->m_TranslationView.x, 960.0f, -960.0f);
    ImGui::SliderFloat3("Model Translation", &this->m_TranslationModel.x, -960.0f, 960.0f);
}

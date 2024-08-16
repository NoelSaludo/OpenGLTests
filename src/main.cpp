#include <format>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include "renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//tests
#include "test/ClearColorTest.h"
#include "test/ObjectColorTest.h"
#include "test/ProjectionsTest.h"
#include "test/TexTest.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto monitor = glfwGetPrimaryMonitor();
    window = glfwCreateWindow(960, 540, "Hello World", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error\n";
    }

    std::cout << glGetString(GL_VERSION) <<'\n';

    {
        Renderer renderer;

        GLCALL(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA))
        GLCALL(glEnable(GL_BLEND))

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();


        test::Test *currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

         testMenu->AddTest<test::ClearColorTest>("Clear color test");
         testMenu->AddTest<test::ObjectColorTest>("Object color test");
         testMenu->AddTest<test::ProjectionsTest>("Projection test");
         testMenu->AddTest<test::TexTest>("Texture test");

        while (!glfwWindowShouldClose(window)){
            GLCALL(glClearColor(0.0f,0.0f,0.0f,1.0f))
            renderer.Clear();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                if(currentTest != testMenu && ImGui::Button("<-")) {
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
            }
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            glfwSwapBuffers(window);

            glfwPollEvents();
        }
        delete testMenu, currentTest;
    }
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}                                                                  

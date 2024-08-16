#pragma once
#include <functional>
#include <string>
#include <vector>

namespace test {
    class Test {
    public:
        Test() = default;
        virtual ~Test() = default;

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}

    };

    class TestMenu : public Test {
    public:
        TestMenu(Test*& currentTest);
        ~TestMenu();

        void OnImGuiRender() override;

        ///
        /// \tparam T takes only classes that inherits from test
        /// \param title title of the function
        /// \brief Adds Tests for the menu
        template <typename T>
        void AddTest(const std::string& title) {
            this->m_Tests.push_back(std::make_pair(title, [](){return new T();}));
        }
    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };

}

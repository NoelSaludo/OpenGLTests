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

        template <typename T>
        void AddTest(const std::string& name);
    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };

    template <typename T>
    void TestMenu::AddTest(const std::string& name) {
        this->m_Tests.push_back(std::make_pair(name, [](){return new T();}));
    }
}

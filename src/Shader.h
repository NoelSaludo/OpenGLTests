#pragma once
#include <string>
#include <unordered_map>

#include "vendor/glm/glm.hpp"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
    std::string m_Filepath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformlocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void SetMat4f(const std::string& name, const glm::mat4& mat);

    unsigned int getMRendererId() const;

    int GetUniformLocation(const std::string& name);
private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(const unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

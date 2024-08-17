#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <format>

#include "Renderer.h"

Shader::Shader(const std::string& filepath) : m_Filepath(filepath), m_RendererID(0) {
    ShaderProgramSource source = this->ParseShader(filepath);
    m_RendererID = this->CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
    GLCALL(glDeleteProgram(m_RendererID))
}

void Shader::Bind() const {
    GLCALL(glUseProgram(m_RendererID))
}

void Shader::Unbind() const {
    GLCALL(glUseProgram(0))
}

void Shader::SetUniform1i(const std::string& name, int value) {
    GLCALL(glUniform1i(this->GetUniformLocation(name),value))
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4) {
    GLCALL(glUniform4f(this->GetUniformLocation(name), v1,v2,v3,v4))
}

void Shader::SetMat4f(const std::string& name, const glm::mat4& mat) {
    GLCALL(glUniformMatrix4fv(this->GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]))
}

int Shader::GetUniformLocation(const std::string& name) {
    if(m_UniformlocationCache.find(name) != m_UniformlocationCache.end())
        return m_UniformlocationCache[name];
    GLCALL(int location = glGetUniformLocation(this->m_RendererID, name.c_str()))
    if(location == -1) {
        std::cout << std::format("Uniform location with the name of {} is not found",name);
        return 0;
    }  else this->m_UniformlocationCache[name] = location;
    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else if (type != ShaderType::NONE) {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(const unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCALL(glShaderSource(id, 1, &src, nullptr))
    GLCALL(glCompileShader(id))

    int result;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result))
    if (!result) {
        int length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length))
        char* message = (char*)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(id, length, &length, message))
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader! " <<
            std::endl;
        std::cout << message << std::endl;
        glDeleteShader(0);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLCALL(unsigned int program = glCreateProgram())
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    if (vs == 0 || fs == 0) {
        std::cout << "Failed to create shader program!" << std::endl;
        return 0;
    }
    GLCALL(glAttachShader(program, vs))
    GLCALL(glAttachShader(program, fs))
    GLCALL(glLinkProgram(program))
    GLCALL(glValidateProgram(program))

    GLCALL(glDeleteShader(vs))
    GLCALL(glDeleteShader(fs))

    return program;
}

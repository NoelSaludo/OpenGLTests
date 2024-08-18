#pragma once
#include <string>

class Texture {
    unsigned int m_RendererID;
    std::string m_filePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(std::string FilePath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    unsigned int getMRendererId() const;

    inline int GetWidth() const {
        return m_Width;
    }

    inline int GetHeight() const {
        return m_Height;
    }
};

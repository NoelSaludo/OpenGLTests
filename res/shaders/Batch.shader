#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 TexCoord;
layout(location = 3) in float Tex;

out vec2 vTexCoord;
out float vtex;
out vec3 vColor;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP*position;
    vtex = Tex;
    vTexCoord = TexCoord;
    vColor = aColor;
}
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vColor;
in float vtex;
in vec2 vTexCoord;

uniform sampler2D u_Textures[2];

void main()
{
    int index = int(vtex);
    color =texture(u_Textures[index], vTexCoord) * vec4(vColor, 1.0);
}
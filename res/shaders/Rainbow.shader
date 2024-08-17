#shader vertex
#version 330 core

layout(location = 0) in vec4 vertices;
layout(location = 1) in vec3 ColorCoord;

out vec3 ourColor;

void main()
{
    gl_Position = vertices;
    ourColor = ColorCoord;
}
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 ourColor;

void main()
{
    color = vec4(ourColor,1.0f);
}
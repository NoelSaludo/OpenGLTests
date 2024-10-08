﻿#shader vertex
#version 330 core  
  
layout(location = 0) in vec4 position; 
layout(location = 1) in vec2 texCoord; 

out vec2 u_TexCoord;

uniform mat4 u_MVP;
  
void main()
{  
   gl_Position = u_MVP*position;
   u_TexCoord = texCoord;
}
#shader fragment
#version 330 core  
  
layout(location = 0) out vec4 color;

uniform vec4 u_Color;

uniform sampler2D u_Texture;

in vec2 u_TexCoord;

void main()  
{
  vec4 texColor = texture(u_Texture, u_TexCoord);
  color = u_Color * texColor;
}
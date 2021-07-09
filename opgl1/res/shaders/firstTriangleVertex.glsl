#version 330 core
layout (location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
out vec3 ourColor;
uniform float xOffset;
uniform vec2 poss;
void main()
{
   //gl_Position = vec4(aPos.x + xOffset, aPos.y, 0.0f, 1.0f);
   gl_Position = vec4(aPos.x + poss.x, aPos.y + poss.y, 0.0f, 1.0f);
   ourColor = aColor;  
}
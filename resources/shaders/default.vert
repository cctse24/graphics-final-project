#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
void main()
{
    gl_Position =  projection_matrix*view_matrix* vec4(aPos.x, 0, aPos.y, 1.0);
}

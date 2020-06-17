#version 420 core

in vec4 fVertexColor;
in vec3 fNormal;

out vec4 FragColor;
void main()
{
    FragColor = vec4(fNormal, 1.0);
}
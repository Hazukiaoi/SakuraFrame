#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 sf_mat_model;
uniform mat4 sf_mat_view;
uniform mat4 sf_mat_projection;

out vec4 vertexColor; 

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); 
}
#version 420 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec2 uv0;
layout (location = 5) in vec2 uv1;

uniform mat4 sf_mat_model;
uniform mat4 sf_mat_view;
uniform mat4 sf_mat_projection;

out vec4 fVertexColor; 
out vec3 fNormal;

void main()
{
    gl_Position = sf_mat_projection * sf_mat_view * sf_mat_model * vec4(position, 1.0);
    // gl_Position = vec4(position, 1.0);
    fVertexColor = color; 
    fNormal = normal;
}
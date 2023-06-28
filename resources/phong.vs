#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 fragPos;
out vec3 normal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
    fragPos = vec3(u_model * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(u_model))) * aNormal;
    
    gl_Position = u_projection * u_view * vec4(fragPos, 1.0);
}

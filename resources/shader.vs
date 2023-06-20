#version 330 core
            
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec4 v_Color;

void main()
{
    v_Color = vec4(a_Normal, 1.0);
    gl_Position = vec4(a_Position, 1.0);
}

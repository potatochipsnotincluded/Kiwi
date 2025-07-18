#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TexCoord;

out gl_PerVertex {
    vec4 gl_Position;
};

void main()
{
    v_TexCoord = a_TexCoord;

    gl_Position = u_Projection * u_View * u_Model * vec4(aPosition, 1.0);
}

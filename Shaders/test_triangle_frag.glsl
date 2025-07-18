#version 460 core

out vec4 FragColor;

uniform sampler2D u_AlbedoMap;

in vec2 v_TexCoord;

void main()
{
    FragColor = texture(u_AlbedoMap, vec2(v_TexCoord.x, 1.0 - v_TexCoord.y));
}
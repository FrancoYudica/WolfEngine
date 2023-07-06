#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_uv;
layout (location = 3) in float a_texture_index;

uniform mat4 u_projection;
uniform mat4 u_view;

out VS_OUT
{
   vec4 color;
   vec2 uv;
   flat float texture_index;
} vs_out;


void main()
{
	vs_out.color = a_color;
   vs_out.uv = a_uv;
   vs_out.texture_index = a_texture_index;
   gl_Position = u_projection * u_view * vec4(a_pos, 1.0);
};
#version 330 core
layout (location = 0) in vec2 aUV;

out vec2 _Uv;

void main()
{
	_Uv = aUV;
   gl_Position = vec4(2.0 * aUV.x - 1.0, 2.0 * aUV.y - 1.0, 0, 1);
};
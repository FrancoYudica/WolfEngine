#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;
out vec4 _Color;
out vec2 _uv;

void main()
{
	_Color = vec4(aUV, 0, 1);
   _uv = aUV;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
};
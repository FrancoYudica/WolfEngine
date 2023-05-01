#version 330 core
out vec4 FragColor;
in vec4 _Color;
in vec2 _uv;
void main()
{
   vec2 pos = _uv - vec2(0.5);
   if (length(pos) > 0.5)
   {
      discard;
   }  
   FragColor = _Color;
};
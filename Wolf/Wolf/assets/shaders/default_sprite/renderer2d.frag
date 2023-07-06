#version 330 core

layout(location = 0) out vec4 FragColor;

in VS_OUT
{
   vec4 color;
   vec2 uv;
   flat int texture_index;
} fs_in;

uniform sampler2D u_texture[32];

void main()
{
   vec4 sampled_texture;
   switch (fs_in.texture_index)
   {

      case 0:
         sampled_texture = texture(u_texture[0], fs_in.uv);
         break;
      case 1:
         sampled_texture = texture(u_texture[1], fs_in.uv);
         break;
      case 2:
         sampled_texture = texture(u_texture[2], fs_in.uv);
            break;
      case 3:
      sampled_texture = texture(u_texture[3], fs_in.uv);
            break;
      case 4:
      sampled_texture = texture(u_texture[4], fs_in.uv);
            break;
      case 5:
      sampled_texture = texture(u_texture[5], fs_in.uv);
            break;
      case 6:
      sampled_texture = texture(u_texture[6], fs_in.uv);
            break;
      case 7:
      sampled_texture = texture(u_texture[7], fs_in.uv);
            break;
      case 8:
      sampled_texture = texture(u_texture[8], fs_in.uv);
            break;
      case 9:
      sampled_texture = texture(u_texture[9], fs_in.uv);
            break;
      case 10:
      sampled_texture = texture(u_texture[10], fs_in.uv);
            break;
      case 11:
      sampled_texture = texture(u_texture[11], fs_in.uv);
            break;
      case 12:
      sampled_texture = texture(u_texture[12], fs_in.uv);
            break;
      case 13:
      sampled_texture = texture(u_texture[13], fs_in.uv);
            break;
      case 14:
      sampled_texture = texture(u_texture[14], fs_in.uv);
            break;
      case 15:
      sampled_texture = texture(u_texture[15], fs_in.uv);
            break;
      case 16:
      sampled_texture = texture(u_texture[16], fs_in.uv);
            break;
      case 17:
      sampled_texture = texture(u_texture[17], fs_in.uv);
            break;
      case 18:
      sampled_texture = texture(u_texture[18], fs_in.uv);
            break;
      case 19:
      sampled_texture = texture(u_texture[19], fs_in.uv);
            break;
      case 20:
      sampled_texture = texture(u_texture[20], fs_in.uv);
            break;
      case 21:
      sampled_texture = texture(u_texture[21], fs_in.uv);
            break;
      case 22:
      sampled_texture = texture(u_texture[22], fs_in.uv);
            break;
      case 23:
      sampled_texture = texture(u_texture[23], fs_in.uv);
            break;
      case 24:
      sampled_texture = texture(u_texture[24], fs_in.uv);
            break;
      case 25:
      sampled_texture = texture(u_texture[25], fs_in.uv);
            break;
      case 26:
      sampled_texture = texture(u_texture[26], fs_in.uv);
            break;
      case 27:
      sampled_texture = texture(u_texture[27], fs_in.uv);
            break;
      case 28:
      sampled_texture = texture(u_texture[28], fs_in.uv);
            break;
      case 29:
      sampled_texture = texture(u_texture[29], fs_in.uv);
            break;
      case 30:
      sampled_texture = texture(u_texture[30], fs_in.uv);
            break;
      case 31:
      sampled_texture = texture(u_texture[31], fs_in.uv);
            break;
      default:
         FragColor = vec4(1.0, 0.4, 0.7, 1.0);
         return;
   }

   FragColor = fs_in.color * sampled_texture;
};
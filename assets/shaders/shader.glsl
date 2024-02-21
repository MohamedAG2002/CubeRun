@type vertex 
#version 460 core 

// Layouts 
layout (location = 0) in vec3 a_pos;

// Uniforms 
uniform mat4 u_view_proj, u_model;

void main()
{
  gl_Position = u_view_proj * u_model * vec4(a_pos, 1.0f);
}

@type fragment 
#version 460 core 

// Outputs 
out vec4 out_color;

// Uniforms 
uniform vec4 u_color;

void main()
{
  out_color = u_color;
}

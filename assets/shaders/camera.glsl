@type vertex
#version 460 core

layout (location = 0) in vec3 aPos; 

uniform mat4 u_model, u_view_projection;

void main() {
  gl_Position = u_view_projection * u_model * vec4(aPos, 1.0f);
}

@type fragment 
#version 460 core 

out vec4 frag_color;

uniform vec4 u_color;

void main() {
  frag_color = u_color;
}

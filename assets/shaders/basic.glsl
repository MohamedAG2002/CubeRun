@type vertex
#version 460 core

layout (location = 0) in vec3 aPos; 

void main() {
  gl_Position = vec4(aPos, 1.0f);
}

@type fragment 
#version 460 core 

out vec4 frag_color;

void main() {
  frag_color = vec4(1.0f);
}

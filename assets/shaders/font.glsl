@type vertex
#version 460 core

layout (location = 0) in vec4 aVertex; // <vec2 = position, vec2 = texture coords> 

out vec2 o_texture_coords;

uniform mat4 u_projection;

void main() {
  gl_Position      = u_projection * vec4(aVertex.xy, 0.0f, 1.0f);
  o_texture_coords = aVertex.zw; 
}

@type fragment 
#version 460 core 

out vec4 frag_color;

in vec2 o_texture_coords;

uniform sampler2D u_text; 
uniform vec4 u_color;

void main() {
  vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(u_text, o_texture_coords).r); 
  frag_color   = vec4(u_color) * sampled;
}

@type vertex 
#version 460 core 

// Layouts 
layout(location = 0) in vec2 a_pos; 
layout(location = 1) in vec4 a_color; 
layout(location = 2) in vec2 a_texture_coords; 
layout(location = 3) in float a_texture_index; 

// Outputs
out VS_OUT {
  vec4 color; 
  vec2 texture_coords;
  flat float texture_index;
} vs_out;

void main() {
  vs_out.color          = a_color;
  vs_out.texture_coords = a_texture_coords;
  vs_out.texture_index  = a_texture_index;

  gl_Position = vec4(a_pos, 0.0f, 1.0f);
}

@type fragment 
#version 460 core 

// Outputs
out vec4 out_color;

// Inputs
in VS_OUT {
  vec4 color; 
  vec2 texture_coords;
  flat float texture_index;
} fs_in;

// Uniforms
uniform sampler2D textures[32];

void main() {
  int index = int(fs_in.texture_index);
  out_color = texture(textures[index], fs_in.texture_coords) * fs_in.color;
}

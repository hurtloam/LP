#version 330

layout(location = 0) in vec4 coord;
//layout(location = 1) in vec2 vertexUV;

//in vec4 coord;
//in vec2 vertexUV;
//layout(location = 0) in vec2 coord
out vec2 texpos;
out vec3 Position_worldspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;

void main(){
  gl_Position = MVP * vec4(coord.xy, 0, 1);
  
  // Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(coord.xy,0,1)).xyz;
  
  texpos = coord.zw;
}
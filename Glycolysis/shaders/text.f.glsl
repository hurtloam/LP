#version 330

in vec2 texpos;
in vec3 Position_worldspace;

// Values that stays constant 
uniform sampler2D tex;
uniform vec4 color;
uniform float useColor;
  
out vec4 m_color;

void main(){
  if (useColor == 1.0) {
    m_color = color;
  }
  else {
    m_color = vec4(1, 1, 1, texture2D(tex, texpos)) * color;
  }
}
  
  

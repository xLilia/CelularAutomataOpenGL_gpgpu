#version 330 core

uniform sampler2D state;
uniform vec2 scale;

in vec2 TexCoord;

out vec4 outColor;

void main() {

     //outColor = vec4(1.0, 0.0, 0.0, 1.0); / scale
	 outColor = texture(state, TexCoord); 
}
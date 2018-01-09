#version 330 core

uniform sampler2D state;
uniform vec2 scale;

out vec4 outColor;

void main() {
     outColor = vec4(1.0, 0.0, 0.0, 1.0);
	 //gl_FragColor = texture2D(state, gl_FragCoord.xy / scale);
}
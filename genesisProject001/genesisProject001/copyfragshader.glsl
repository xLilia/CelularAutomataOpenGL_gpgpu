#version 330 core

uniform sampler2D state;
uniform vec2 scale1;

//in vec2 TexCoord;

out vec4 outColor;

void main() {

     //outColor = vec4(1.0, 0.0, 0.0, 1.0); 
	 //outColor = vec4(scale, 1.0, 1.0); 
	 //outColor = texture(state, TexCoord);
	 //vec2 ts = vec2(512,512);
	 //vec2 tc = ((gl_FragCoord.xy) / scale.xy);
	 //outColor = texture(state, tc);
	 //outColor = texture(state, gl_FragCoord.rg ); 
	 outColor = texture2D(state, gl_FragCoord.xy / scale1);
	 
}
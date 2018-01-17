#version 330 core

uniform sampler2D state;
uniform vec2 scale0;

in vec3 Color;
in vec2 TexCoord;

out vec4 outColor;

void main(){
	//vec2 current = get(vec2(0.0, 0.0));
    //outColor = vec4(current.x, current.y, 0.0, 1.0);
	outColor = vec4(TexCoord, 0.0, 1.0);
	//outColor = texture(state, gl_FragCoord.xy);

}
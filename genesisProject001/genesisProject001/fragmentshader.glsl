#version 330 core

uniform sampler2D state;
uniform vec2 scale0;

in vec3 Color;
in vec2 TexCoord;

out vec4 outColor;

int get(vec2 offset){
	return int(texture(state, (gl_FragCoord.xy + offset) / scale0).r); 
}

void main(){

	//int current = get(vec2(0.0, 0.0));
	//gl_FragColor = vec4(current, current, current, 1.0);
	
	int sum =
        get(vec2(-1.0, -1.0)) +
        get(vec2(-1.0,  0.0)) +
        get(vec2(-1.0,  1.0)) +
        get(vec2( 0.0, -1.0)) +
        get(vec2( 0.0,  1.0)) +
        get(vec2( 1.0, -1.0)) +
        get(vec2( 1.0,  0.0)) +
        get(vec2( 1.0,  1.0));
    if (sum == 3) {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    } else if (sum == 2) {
        float current = float(get(vec2(0.0, 0.0)));
        gl_FragColor = vec4(current, current, current, 1.0);
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }

	//outColor = vec4(TexCoord, 0.0, 1.0);
	//outColor = texture(state, gl_FragCoord.xy);

}
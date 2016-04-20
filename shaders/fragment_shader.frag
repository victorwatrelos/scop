#version 400
out vec4 frag_color;
in vec3 fragment_color;
in float out_Fade;
uniform sampler2D tex;

void main()
{
	//frag_color = vec4(vec3(1.0, 0.0, 0.0), 1.0);
	vec2 texcoord = abs((fragment_color.xy + 1.0 + fragment_color.z) / 2.0f);
	float n = float(gl_PrimitiveID % 10) / 10.0;
	frag_color = texture(tex, texcoord) * out_Fade + n * (1.0 - out_Fade);
}

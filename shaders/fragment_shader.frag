#version 400
out vec4 frag_color;
in vec3 fragment_color;
in float out_Fade;
in float tex_clipping;
uniform sampler2D tex;

void main()
{
	vec2 texcoord;
	if (tex_clipping < 0.f)
		texcoord = abs((fragment_color.xy + 1.0 + fragment_color.z) / 2.0f);
	else
		texcoord = abs((fragment_color.xy + 1.0) / 2.0f);
	float n = float(gl_PrimitiveID % 10) / 10.0;
	frag_color = texture(tex, texcoord) * out_Fade + n * (1.0 - out_Fade);
}

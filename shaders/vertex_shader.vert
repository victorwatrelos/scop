#version 400

uniform mat4 P;
uniform mat4 R;
uniform vec4 T;
uniform float FADE;
uniform int TEX;

in vec3 in_Position;
in vec3 in_Color;

out float tex_clipping;
out vec3 fragment_color;
out float out_Fade;

void main()
{
	vec4	t;

	gl_Position = P * (vec4(in_Position, 1.0) * R + T);
	fragment_color = in_Position;
	out_Fade = FADE;
	if (TEX == 0)
		tex_clipping = -1.f;
	else
		tex_clipping = 1.f;
}

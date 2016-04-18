#version 400

uniform mat4 P;
uniform mat4 R;

in vec3 in_Position;
in vec3 in_Color;

out vec3 fragment_color;

void main()
{
	vec4	t;

	t = vec4(0.0, 0.0, -10.0, 0.0);
	gl_Position = P * (vec4(in_Position, 1.0) * R + t);
	fragment_color = in_Color;
}

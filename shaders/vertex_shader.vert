#version 400

uniform mat4 P;

in vec3 vp;

void main()
{
	vec3	t;

	t = vec3(0.0, 0.0, -5.0);
	gl_Position = P * vec4(t + vp, 1.0);
}

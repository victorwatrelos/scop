#version 400
out vec4 frag_color;
in vec3 fragment_color;

void main()
{
	frag_color = vec4(fragment_color, 1.0);
}

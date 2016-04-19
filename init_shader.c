#include "init_shader.h"

GLuint	get_shader(const char *shader_code, GLenum shader_type, int *err)
{
	GLuint		shader;
	GLint		shader_ok;
    GLsizei		log_length;
    char		info_log[8192];

	shader = glCreateShader(shader_type);
	glShaderSource (shader, 1, &shader_code, NULL);
	glCompileShader (shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
	if (shader_ok != GL_TRUE)
	{
		ft_printf("ERROR: Failed to compile shader\n");
		glGetShaderInfoLog(shader, 8192, &log_length,info_log);
		ft_printf("ERROR: \n%s\n\n", info_log);
		glDeleteShader(shader);
		*err = 1;
		return (0);
	}
	*err = 0;
	return (shader);
}

int		init_shader(t_opengl *opengl)
{
	const char*	vertex_shader;
	const char*	fragment_shader;
	int		err;

	if (!(vertex_shader = filetobuf("shaders/vertex_shader.vert", NULL))
			|| !(fragment_shader = filetobuf("shaders/fragment_shader.frag", NULL)))
	{
		ft_printf("ERROR: Unable to open shader files\n");
		return (0);
	}
	ft_printf("Loading vertex shader\n");
	opengl->vs = get_shader(vertex_shader, GL_VERTEX_SHADER, &err);
	if (err)
		return (0);
	ft_printf("Loading fragment shader\n");
	opengl->fs = get_shader(fragment_shader, GL_FRAGMENT_SHADER, &err);
	if (err)
		return (0);
	if (!(opengl->shader_program = glCreateProgram()))
		return (0);
	glAttachShader(opengl->shader_program, opengl->fs);
	glAttachShader(opengl->shader_program, opengl->vs);
	glLinkProgram(opengl->shader_program);
	return (1);
}

#include "init_opengl.h"

static void		init_buffer(t_opengl *opengl)
{
	GLuint						attrloc;
	t_array						*tmp;

	glGenVertexArrays(1, &(opengl->vao));
	glBindVertexArray(opengl->vao);
	tmp = opengl->obj.buffers + VERTICES;
	glGenBuffers(3, opengl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, opengl->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * tmp->nb_entry,
			tmp->value, GL_STATIC_DRAW);
	attrloc = glGetAttribLocation(opengl->shader_program, "in_Position");
	glVertexAttribPointer(attrloc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrloc);
	tmp = opengl->obj.buffers + INDEXES;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl->vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * tmp->nb_entry,
			tmp->value, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

static int		init_textures(t_opengl *opengl)
{
	int		reso[2];
	uint8_t	*res;

	if (!(res = bmp_parser("tex.bmp", reso)))
		return (0);
	glGenTextures(1, &(opengl->tex));
	glBindTexture(GL_TEXTURE_2D, opengl->tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, reso[0],
			reso[1], 0, GL_BGRA, GL_UNSIGNED_BYTE, res);
	free(res);
	return (1);
}

static void		set_uniform(t_opengl *opengl)
{
	opengl->uloc_p = glGetUniformLocation(opengl->shader_program, "P");
	opengl->uloc_r = glGetUniformLocation(opengl->shader_program, "R");
	opengl->uloc_t = glGetUniformLocation(opengl->shader_program, "T");
	opengl->uloc_tex = glGetUniformLocation(opengl->shader_program, "TEX");
	opengl->uloc_fade = glGetUniformLocation(opengl->shader_program, "FADE");
	opengl->rot_matrix = get_rot_m(0.0f);
	opengl->proj_matrix = get_projection(45, 640 / 480, 0.1, 100);
	glUniformMatrix4fv(opengl->uloc_p, 1, GL_FALSE, opengl->proj_matrix);
	glUniformMatrix4fv(opengl->uloc_r, 1, GL_FALSE, opengl->rot_matrix);
	glUniform4f(opengl->uloc_t, opengl->trans.x, opengl->trans.y,
			opengl->trans.z, 1.0f);
	glUniform1f(opengl->uloc_fade, 0.0f);
	glUniform1i(opengl->uloc_tex, opengl->ctrl.clipping);
}

void			init_opengl(t_opengl *opengl, int width, int height)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glViewport(0, 0, width, height);
	if (!init_shader(opengl))
	{
		ft_printf("ERROR: init_shader fail\n");
		exit(1);
	}
	if (!init_textures(opengl))
	{
		ft_printf("ERROR: init_textures fail\n");
		exit(1);
	}
	init_buffer(opengl);
	glUseProgram(opengl->shader_program);
	set_uniform(opengl);
}

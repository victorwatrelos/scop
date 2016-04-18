#ifndef STRUCT_H
# define STRUCT_H

# include "opengl_inc.h"

typedef struct		s_view
{
		float		axis[3][3];
		float		eye_pos[3];
}					t_view;

typedef struct		s_obj
{
	GLfloat			*vertices;
	size_t			nb_vertices;
	GLfloat			*colors;
	size_t			nb_colors;
	GLuint			*indexes;
	size_t			nb_indexes;
	const char		*file_name;
}					t_obj;

typedef struct		s_opengl
{
		GLFWwindow	*window;
		GLuint		vs;
		GLuint		fs;
		GLuint		vbo[3];
		GLuint		vao;
		GLuint		shader_program;
		t_view		view;
		float		*proj_matrix;
		float		*rot_matrix;
		GLint		uloc_P;
		GLint		uloc_R;
		t_obj		obj;
}					t_opengl;

#endif

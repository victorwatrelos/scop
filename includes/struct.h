#ifndef STRUCT_H
# define STRUCT_H

# include "opengl_inc.h"

typedef struct		s_view
{
		float		axis[3][3];
		float		eye_pos[3];
}					t_view;

typedef struct		s_opengl
{
		GLFWwindow	*window;
		GLuint		vs;
		GLuint		fs;
		GLuint		vbo;
		GLuint		vao;
		GLuint		shader_program;
		t_view		view;
		float		*proj_matrix;
		float		*view_matrix;
		GLint		uloc_P;
		GLint		uloc_V;
}					t_opengl;

#endif

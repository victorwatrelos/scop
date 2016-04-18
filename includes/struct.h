#ifndef STRUCT_H
# define STRUCT_H

# include "opengl_inc.h"

typedef struct		s_view
{
		float		axis[3][3];
		float		eye_pos[3];
}					t_view;

typedef struct		s_array
{
	void			*value;
	size_t			size;
	size_t			size_alloc;
	size_t			nb_entry;
}					t_array;

# define VERTICES 0
# define COLORS 1
# define INDEXES 2

typedef struct		s_obj
{
	t_array			buffers[3];
	const char		*file_name;
}					t_obj;

typedef struct		s_opengl
{
		GLFWwindow	*window;
		GLuint		vs;
		GLuint		fs;
		GLuint		vbo[3];
		GLuint		vao;
		GLuint		tex;
		GLuint		shader_program;
		t_view		view;
		float		*proj_matrix;
		float		*rot_matrix;
		GLint		uloc_P;
		GLint		uloc_R;
		t_obj		obj;
}					t_opengl;

#endif

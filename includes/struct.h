#ifndef STRUCT_H
# define STRUCT_H

# include "opengl_inc.h"

typedef struct		s_view
{
	float			axis[3][3];
	float			eye_pos[3];
}					t_view;

typedef struct		s_array
{
	void			*value;
	size_t			size;
	size_t			size_alloc;
	size_t			nb_entry;
}					t_array;

# define VERTICES 0
# define INDEXES 1

typedef struct		s_obj
{
	t_array			buffers[2];
	const char		*file_name;
}					t_obj;

# define LEFT 0
# define RIGHT 1
# define FRONT 2
# define BACK 3
# define UP 4
# define DOWN 5
# define STEP 0.1f

typedef struct		s_control
{
	int				dir[6];
	int				display_tex;
	float			step;
	float			intensity;
	int				is_changing;
}					t_control;

typedef struct		s_vec3
{
	GLfloat			x;
	GLfloat			y;
	GLfloat			z;
}					t_vec3;

typedef struct		s_opengl
{
	GLFWwindow		*window;
	GLuint			vs;
	GLuint			fs;
	GLuint			vbo[3];
	GLuint			vao;
	GLuint			tex;
	GLuint			shader_program;
	t_view			view;
	float			*proj_matrix;
	float			*rot_matrix;
	GLint			uloc_p;
	GLint			uloc_r;
	GLint			uloc_t;
	GLint			uloc_fade;
	t_obj			obj;
	t_control		ctrl;
	t_vec3			trans;
}					t_opengl;

#endif

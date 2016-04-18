#include "init_opengl.h"

static void		setGlfwWindowHint(void)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
//	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
//	glfwWindowHint(GLFW_DEPTH_BITS, 24);
  	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void		error_callback(int error, const char* description)
{
	ft_printf("error: %d, %s\n", error, description);
}

static void		init_buffer(t_opengl *opengl)
{

	GLuint						attrloc;
	t_array						*tmp;

	glGenVertexArrays(1, &(opengl->vao));
	glBindVertexArray(opengl->vao);

	tmp = opengl->obj.buffers + VERTICES;
	glGenBuffers(3, opengl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, opengl->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * tmp->nb_entry, tmp->value, GL_STATIC_DRAW);
	attrloc = glGetAttribLocation(opengl->shader_program, "in_Position");
	glVertexAttribPointer(attrloc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrloc);

	tmp = opengl->obj.buffers + COLORS;
	glBindBuffer(GL_ARRAY_BUFFER, opengl->vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * tmp->nb_entry, tmp->value, GL_STATIC_DRAW);
	attrloc = glGetAttribLocation(opengl->shader_program, "in_Color");
	glVertexAttribPointer(attrloc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrloc);

	tmp = opengl->obj.buffers + INDEXES;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl->vbo[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * tmp->nb_entry, tmp->value, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

static void		init_view(t_view *view)
{
	ft_bzero(view, sizeof(t_view));
	view->axis[0][0] = 1.f;
	view->axis[1][1] = 1.f;
	view->axis[2][2] = 1.f;
}

static void		init_textures(t_opengl *opengl)
{
	glGenTextures(1, &(opengl->tex));
	glBindTexture(GL_TEXTURE_2D, opengl->tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	GLfloat pixels[] = {
		0.5f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,   0.5f, 0.0f, 0.0f
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
}

void			init_opengl(t_opengl *opengl)
{
    int     width;
    int		height;

	ft_printf("Start parsing\n");
	if (!(parse_file(&(opengl->obj))))
		exit(1);
	ft_printf("Start glfw initalisation\n");
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(1);
    setGlfwWindowHint();
    opengl->window = glfwCreateWindow(640, 480, "scop", NULL, NULL);
    if (!opengl->window)
	{
		glfwTerminate();
		exit(1);
	}
	ft_printf("HERE2\n");
	glfwMakeContextCurrent(opengl->window);
	glfwSwapInterval(1);
	ft_printf("Start opengl initalisation\n");
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glfwGetFramebufferSize(opengl->window, &(width), &(height));
	glViewport(0, 0, width, height);
	if (!init_shader(opengl))
	{
		ft_printf("ERROR: init_shader fail\n");
		exit(1);
	}
	init_view(&(opengl->view));
	init_textures(opengl);
	init_buffer(opengl);
	glUseProgram (opengl->shader_program);
	opengl->uloc_P = glGetUniformLocation(opengl->shader_program, "P");
	opengl->uloc_R = glGetUniformLocation(opengl->shader_program, "R");
	opengl->rot_matrix = get_rot_matrix(0.0f);
	opengl->proj_matrix = get_projection(45, 640 / 480, 0.1, 100);
	glUniformMatrix4fv(opengl->uloc_P, 1, GL_FALSE, opengl->proj_matrix);
	glUniformMatrix4fv(opengl->uloc_R, 1, GL_FALSE, opengl->rot_matrix);
	ft_printf("Let's go\n");
	launch_loop(opengl);
}

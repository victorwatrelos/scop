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

static void		error_callback(int error, const char* description)
{
	ft_printf("error: %d, %s\n", error, description);
}

static void		init_buffer(t_opengl *opengl)
{
static const GLfloat cube_points[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};
	glGenBuffers(1, &(opengl->vbo));
	glBindBuffer(GL_ARRAY_BUFFER, opengl->vbo);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof (float), cube_points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &(opengl->vao));
	glBindVertexArray(opengl->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, opengl->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

static void		init_view(t_view *view)
{
	ft_bzero(view, sizeof(t_view));
	view->axis[0][0] = 1.f;
	view->axis[1][1] = 1.f;
	view->axis[2][2] = 1.f;
}

void			init_opengl(t_opengl *opengl)
{
    int     width;
    int		height;

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
	glfwMakeContextCurrent(opengl->window);
	glfwSwapInterval(1);
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
	init_buffer(opengl);
	glUseProgram (opengl->shader_program);
	opengl->uloc_P = glGetUniformLocation(opengl->shader_program, "P");
	opengl->uloc_V = glGetUniformLocation(opengl->shader_program, "V");
	opengl->view_matrix = get_view_matrix(&(opengl->view));
	opengl->proj_matrix = get_projection(45, 640 / 480, 0.1, 100);
	glUniformMatrix4fv(opengl->uloc_P, 1, GL_FALSE, opengl->proj_matrix);
	launch_loop(opengl);
}

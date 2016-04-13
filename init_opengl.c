#include "init_opengl.h"

static void		setGlfwWindowHint(void)
{
	/*
	glfwWindowHint(GLFW_SAMPLES, 4);
//	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
//	glfwWindowHint(GLFW_DEPTH_BITS, 24);
  	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    */

	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

static void		error_callback(int error, const char* description)
{
	ft_printf("error: %d, %s\n", error, description);
}

void			init_opengl(t_opengl *opengl)
{
    int     width;
    int		height;

    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(0);
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
	display_test(opengl);
}

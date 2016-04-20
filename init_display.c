#include "init_display.h"

static void		setGlfwWindowHint(void)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
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

static void		init_glfw(t_opengl *opengl)
{
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
	glfwSetWindowUserPointer(opengl->window, opengl);
    glfwSetKeyCallback(opengl->window, key_callback);
}

void	init_display(t_opengl *opengl)
{
    int     width;
    int		height;

	ft_printf("Start parsing\n");
	if (!(parse_file(&(opengl->obj))))
		exit(1);
	ft_printf("Start glfw initalisation\n");
	init_glfw(opengl);
	glfwGetFramebufferSize(opengl->window, &(width), &(height));
	ft_printf("Start opengl initalisation\n");
	init_opengl(opengl, width, height);
	ft_printf("Let's go\n");
	opengl->trans.z = -10.0f;
	launch_loop(opengl);
	ft_printf("Release ressources\n");
	terminate_opengl(opengl);
}

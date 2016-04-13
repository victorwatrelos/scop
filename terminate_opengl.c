#include "terminate_opengl.h"

void		terminate_opengl(t_opengl *opengl)
{
	(void)opengl;
	glfwTerminate();
}

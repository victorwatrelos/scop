#include "terminate_opengl.h"

void		terminate_opengl(t_opengl *opengl)
{
	glDeleteProgram(opengl->shader_program);
	glfwTerminate();
	free(opengl->proj_matrix);
	free(opengl->rot_matrix);
	free(opengl->obj.buffers[VERTICES].value);
	free(opengl->obj.buffers[INDEXES].value);
}

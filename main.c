#include <GLFW/glfw3.h>
#include "init_opengl.h"

int main(void)
{
	t_opengl	opengl;

	ft_bzero(&opengl, sizeof(opengl));
	init_opengl(&opengl);
}

#include <GLFW/glfw3.h>
#include "init_opengl.h"
#include <ft_printf.h>

int main(int ac, char **av)
{
	t_opengl	opengl;

	if (ac < 2)
	{
		ft_printf("./scop file.obj\n");
		return (1);
	}
	ft_bzero(&opengl, sizeof(opengl));
	opengl.obj.file_name = av[1];
	init_opengl(&opengl);
}

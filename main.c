/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:53:51 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:53:54 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLFW/glfw3.h>
#include "init_display.h"
#include <ft_printf.h>

int	main(int ac, char **av)
{
	t_opengl	opengl;

	if (ac < 2)
	{
		ft_printf("./scop file.obj\n");
		return (1);
	}
	ft_bzero(&opengl, sizeof(opengl));
	opengl.obj.file_name = av[1];
	init_display(&opengl);
	return (0);
}

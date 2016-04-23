/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_opengl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:53:51 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:53:54 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

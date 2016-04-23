/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_callback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:53:51 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:53:54 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glfw_callback.h"

static void		switch_tex(t_control *ctrl)
{
	ctrl->display_tex = !ctrl->display_tex;
	if (ctrl->display_tex)
		ctrl->step = 0.05f;
	else
		ctrl->step = -0.05f;
	ctrl->is_changing = 1;
}

static void		key_press(int key, t_control *ctrl)
{
	if (key == 'A')
		ctrl->dir[LEFT] = 1;
	else if (key == 'D')
		ctrl->dir[RIGHT] = 1;
	else if (key == 'W')
		ctrl->dir[FRONT] = 1;
	else if (key == 'S')
		ctrl->dir[BACK] = 1;
	else if (key == 'Q')
		ctrl->dir[UP] = 1;
	else if (key == 'E')
		ctrl->dir[DOWN] = 1;
	else if (key == 'R')
		switch_tex(ctrl);
	else if (key == 'T')
		ctrl->clipping = !ctrl->clipping;
}

void			key_callback(GLFWwindow *window, int key,
		int scancode, int action, int mods)
{
	t_opengl		*ptr;
	t_control		*ctrl;

	(void)scancode;
	(void)mods;
	ptr = (t_opengl *)(glfwGetWindowUserPointer(window));
	ctrl = &(ptr->ctrl);
	if (action == GLFW_PRESS)
		key_press(key, ctrl);
	else if (action == GLFW_RELEASE)
	{
		if (key == 'A')
			ctrl->dir[LEFT] = 0;
		else if (key == 'D')
			ctrl->dir[RIGHT] = 0;
		else if (key == 'W')
			ctrl->dir[FRONT] = 0;
		else if (key == 'S')
			ctrl->dir[BACK] = 0;
		else if (key == 'Q')
			ctrl->dir[UP] = 0;
		else if (key == 'E')
			ctrl->dir[DOWN] = 0;
	}
}

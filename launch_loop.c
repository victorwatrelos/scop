/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:53:51 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:53:54 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_opengl.h"

static void			do_move(t_opengl *opengl)
{
	t_control	*ctrl;

	ctrl = &(opengl->ctrl);
	if (ctrl->dir[DOWN])
		opengl->trans.y -= STEP;
	if (ctrl->dir[UP])
		opengl->trans.y += STEP;
	if (ctrl->dir[LEFT])
		opengl->trans.x -= STEP;
	if (ctrl->dir[RIGHT])
		opengl->trans.x += STEP;
	if (ctrl->dir[FRONT])
		opengl->trans.z -= STEP;
	if (ctrl->dir[BACK])
		opengl->trans.z += STEP;
}

static void			do_trans_tex(t_opengl *opengl)
{
	t_control *ctrl;

	ctrl = &(opengl->ctrl);
	if (!ctrl->is_changing)
		return ;
	ctrl->intensity += ctrl->step;
	if (ctrl->step < 0.f && ctrl->intensity < 0.f)
	{
		ctrl->is_changing = 0;
		ctrl->intensity = 0.f;
	}
	if (ctrl->step > 0.f && ctrl->intensity > 1.f)
	{
		ctrl->is_changing = 0;
		ctrl->intensity = 1.f;
	}
	glUniform1f(opengl->uloc_fade, ctrl->intensity);
}

static void			set_uniform(t_opengl *opengl, float alpha)
{
	float	*rm;

	glUniformMatrix4fv(opengl->uloc_r, 1, GL_FALSE, rm = get_rot_m(alpha));
	free(rm);
	glUniform4f(opengl->uloc_t, opengl->trans.x,
			opengl->trans.y, opengl->trans.z, 1.0f);
	glUniform1i(opengl->uloc_tex, opengl->ctrl.clipping);
}

void				launch_loop(t_opengl *opengl)
{
	float	alpha;

	alpha = 0.f;
	while (!glfwWindowShouldClose(opengl->window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(opengl->shader_program);
		set_uniform(opengl, alpha);
		glBindVertexArray(opengl->vao);
		glDrawElements(GL_TRIANGLES, opengl->obj.buffers[INDEXES].nb_entry,
				GL_UNSIGNED_INT, 0);
		glfwPollEvents();
		glfwSwapBuffers(opengl->window);
		do_move(opengl);
		do_trans_tex(opengl);
		alpha += 0.01f;
		if (alpha > 2 * M_PI)
			alpha -= 2 * M_PI;
	}
	glDeleteShader(opengl->fs);
	glDeleteShader(opengl->vs);
}

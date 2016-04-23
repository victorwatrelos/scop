/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_callback.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:54:07 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:54:10 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFW_CALLBACK_H
# define GLFW_CALLBACK_H

# include "opengl_inc.h"
# include "struct.h"
# include <stdio.h>
# include <libft.h>
# include <ft_printf.h>

void	key_callback(GLFWwindow *window, int key, int scancode,
		int action, int mods);

#endif

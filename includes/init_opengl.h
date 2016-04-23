/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opengl.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:54:07 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:54:10 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_OPENGL_H
# define INIT_OPENGL_H

# include <libft.h>
# include <ft_printf.h>
# include "struct.h"
# include "opengl_inc.h"
# include "matrix_calcul.h"
# include "init_shader.h"
# include "parser.h"
# include "bmp_parser.h"
# include "glfw_callback.h"

void			init_opengl(t_opengl *opengl, int width, int height);

#endif

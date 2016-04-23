/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:54:07 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:54:10 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_DISPLAY_H
# define INIT_DISPLAY_H

# include "init_opengl.h"
# include "terminate_opengl.h"

void	init_display(t_opengl *opengl);
void	launch_loop(t_opengl *opengl);

#endif

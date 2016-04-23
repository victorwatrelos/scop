/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwatrelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 14:54:07 by vwatrelo          #+#    #+#             */
/*   Updated: 2016/04/23 14:54:10 by vwatrelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"
# include <stdlib.h>
# include <libft.h>
# include <ft_printf.h>
# include <errno.h>
# include <string.h>
# include "to_center.h"
# define MAX_STR_SIZE 2048

int		parse_file(t_obj *obj);
void	get_face(char *str, t_array *array);
size_t	get_nb_index(char *str);

#endif

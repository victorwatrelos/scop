# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vwatrelo <vwatrelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/21 12:04:58 by vwatrelo          #+#    #+#              #
#    Updated: 2014/02/12 16:54:13 by vwatrelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang
FLAGS=-Wall -Wextra -Werror
NAME=libft.a
INCLUDES=-I includes/
LIB=ft_printf/libft_printf.a \
	libft_core/libft_core.a \
	list/libft_list.a

.PHONY: clean fclean all re
.SILENT:
all: $(NAME)

$(NAME): libft

libft: $(LIB)
	$(foreach var, $(LIB), mv $(var) $(notdir $(var)) ;)

ft_printf/libft_printf.a:
	make -C ft_printf

list/libft_list.a:
	make -C list

libft_core/libft_core.a:
	make -C libft_core

clean:
	make clean -C libft_core
	make clean -C ft_printf
	make clean -C list

fclean: clean
	rm -f $(notdir $(LIB))

re: fclean all

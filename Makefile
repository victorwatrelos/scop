CC= gcc
FLAGS= -Wall -Wextra -Werror -g
SRC_SCOP = main.c \
		   terminate_opengl.c \
		   launch_loop.c \
		   init_shader.c \
		   matrix_calcul.c \
		   parser.c \
		   utils.c \
		   bmp_parser.c \
		   init_opengl.c

OBJ_SCOP= $(SRC_SCOP:.c=.o)

NAME_SCOP=ft_scop
LIB=-L./libft -lft_core -lft_list -lft_printf -L./libs -lglfw3
DIR_LFT=./libft
INCLUDES=-I ./libft/includes -I ./includes
FRWK=-framework Cocoa \
	-framework OpenGL \
	-framework AGL \
	-framework IOKit \
	-framework CoreVideo \
	-framework CoreFoundation

.PHONY: clean fclean re all

.SILENT:

all: $(NAME_SCOP)

$(NAME_SCOP): $(OBJ_SCOP)
	(cd $(DIR_LFT) ; make )
	$(CC) -o $(NAME_SCOP) $(OBJ_SCOP) $(LIB) $(FLAGS) $(FRWK)
	echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME_SCOP) \033[0mDONE!"

%.o: %.c
	echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m"
	$(CC) -c $(FLAGS) -o $@ $< $(INCLUDES)

clean:
	(cd $(DIR_LFT) ; make clean)
	echo "\t\xF0\x9F\x92\xA3   Cleaning"
	rm -rf $(OBJ_SCOP)

fclean: clean
	(cd $(DIR_LFT) ; make fclean)
	echo "\t\xF0\x9F\x9A\xBD   Full Clean"
	rm -rf $(NAME_SCOP)

re: fclean all

#ifndef BMP_PARSER_H
# define BMP_PARSER_H

# include "utils.h"
# include <libft.h>
# define SIZE_HEADER 14
# define SIZE_INFO 40
# define SIZE_SHORT sizeof(unsigned short int)
# define SIZE_INT sizeof(unsigned int)

uint8_t		*bmp_parser(const char *file_name, int *reso);

#endif

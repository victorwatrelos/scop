#ifndef BMP_PARSER_H
# define BMP_PARSER_H

# include "utils.h"
# include <libft.h>

uint8_t		*bmp_parser(const char *file_name, int *reso);

typedef struct __attribute__((__packed__))	s_bmp_header
{
	unsigned short int						type;
	unsigned int							size;
	unsigned short int						reserved1;
	unsigned short int						reserved2;
	unsigned int							offset;
}											t_bmp_header;

typedef struct __attribute__((__packed__))	s_bmp_info
{
	unsigned int							size;
	int										width;
	int										height;
	unsigned short int						planes;
	unsigned short int						bits;
	unsigned int							compression;
	unsigned int							imagesize;
	int										xresolution;
	int										yresolution;
	unsigned int 							ncolours;
	unsigned int 							importantcolours;
}											t_bmp_info;

#endif

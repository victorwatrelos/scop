#include "bmp_parser.h"

static unsigned int	get_file_header(void *data, size_t size, int *res)
{
	size_t			tot_size;
	unsigned int	size_header;
	unsigned int	offset;

	if (size < SIZE_HEADER + SIZE_INFO)
		return (0);
	size_header = *(unsigned int *)(data + SIZE_SHORT);
	offset = *(unsigned int *)(data + (SIZE_SHORT * 3) + SIZE_INT);
	if (size_header != size)
		return (0);
	res[0] = *(int *)(data + SIZE_HEADER + SIZE_INT);
	res[1] = *(int *)(data + SIZE_HEADER + SIZE_INT + SIZE_INT);
	tot_size = res[0] * res[1] * 4;
	if ((size - offset) < (unsigned long)(tot_size))
		return (0);
	return (offset);
}

void				update_data(uint8_t *data, size_t size)
{
	size_t		i;
	uint8_t		*tmp_ptr;
	uint8_t		alpha;

	i = 0;
	while (i < size)
	{
		tmp_ptr = data + i;
		alpha = tmp_ptr[0];
		tmp_ptr[0] = tmp_ptr[1];
		tmp_ptr[1] = tmp_ptr[2];
		tmp_ptr[2] = tmp_ptr[3];
		i += 4;
	}
}

uint8_t				*bmp_parser(const char *file_name, int *reso)
{
	uint8_t			*tmp;
	uint8_t			*res;
	size_t			size;
	size_t			offset;

	if (!(tmp = (uint8_t *)filetobuf(file_name, &size)))
		return (NULL);
	if (!(offset = get_file_header(tmp, size, reso)))
	{
		free(tmp);
		ft_printf("BMP file %s is not valid\n", file_name);
		return (NULL);
	}
	size = (size_t)((reso[0] * reso[1]) * 4);
	if (!(res = malloc(size)))
	{
		free(tmp);
		return (NULL);
	}
	ft_memcpy(res, tmp + offset, size);
	free(tmp);
	update_data(res, size);
	return (res);
}

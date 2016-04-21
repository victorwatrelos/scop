#include "bmp_parser.h"

static unsigned int	get_file_header(void *data, size_t size, int *res)
{
	t_bmp_header	*header;
	t_bmp_info		*info;
	size_t			tot_size;

	if (size < sizeof(t_bmp_header) + sizeof(t_bmp_info))
		return (0);
	header = (t_bmp_header *)data;
	info = (t_bmp_info *)(data + sizeof(t_bmp_header));
	if (header->size != size)
		return (0);
	tot_size = info->width * info->height * 3;
	if ((size - header->offset) < (unsigned long)(tot_size))
		return (0);
	res[0] = info->width;
	res[1] = info->height;
	return (header->offset);
}

void				update_data(uint8_t *data, size_t size)
{
	size_t		i;
	uint8_t		*tmp_ptr;

	i = 0;
	while (i < size)
	{
		tmp_ptr = data + i;
		tmp_ptr[0] = tmp_ptr[0];
		tmp_ptr[1] = tmp_ptr[1];
		tmp_ptr[2] = tmp_ptr[2];
		i += 3;
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

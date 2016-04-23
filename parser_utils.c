#include "parser.h"

size_t			get_nb_index(char *str)
{
	GLuint	val[4];
	size_t	nb_val;

	nb_val = sscanf(str, "f %u %u %u %u\n", val, val + 1, val + 2, val + 3);
	if (nb_val == 4)
		nb_val = 6;
	return (nb_val);
}

static void		val_4_create(GLuint *ptr_uint, GLuint *val, t_array *array)
{
	ptr_uint[0] = val[0];
	ptr_uint[1] = val[1];
	ptr_uint[2] = val[2];
	ptr_uint[3] = val[0];
	ptr_uint[4] = val[2];
	ptr_uint[5] = val[3];
	array->size += sizeof(GLuint) * 6;
	array->nb_entry += 6;
}

void			get_face(char *str, t_array *array)
{
	GLuint	val[4];
	size_t	nb_val;
	size_t	i;
	GLuint	*ptr_uint;

	ptr_uint = (GLuint *)array->value;
	nb_val = sscanf(str, "f %u %u %u %u\n", val, val + 1, val + 2, val + 3);
	i = 0;
	while (i < nb_val)
	{
		val[i++]--;
	}
	if (nb_val == 4)
	{
		val_4_create(ptr_uint + array->nb_entry, val, array);
		return ;
	}
	i = 0;
	while (i < nb_val)
	{
		ptr_uint[array->nb_entry] = val[i];
		array->nb_entry++;
		++i;
	}
	array->size += sizeof(GLuint) * nb_val;
}

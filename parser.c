#include "parser.h"

static int			get_vertice(char *str, t_array *array)
{
	float	val[3];
	size_t	nb_val;
	size_t	i;
	GLfloat	*ptr_float;

	ptr_float = (GLfloat *)array->value;
	nb_val = sscanf(str, "v %e %e %e\n", val, val + 1, val + 2);
	if (nb_val != 3)
		return (0);
	i = 0;
	while (i < nb_val)
	{
		ptr_float[array->nb_entry] = val[i];
		array->nb_entry++;
		++i;
	}
	array->size += sizeof(GLfloat) * nb_val;
	return (1);
}

static int			allocate_array(t_obj *obj)
{
	t_array	*tmp;

	tmp = obj->buffers + INDEXES;
	tmp->size_alloc = sizeof(GLuint) * obj->buffers[INDEXES].nb_entry;
	if (!(tmp->value = malloc(tmp->size_alloc)))
		return (0);
	tmp->nb_entry = 0;
	tmp = obj->buffers + VERTICES;
	tmp->size_alloc = sizeof(GLfloat) * obj->buffers[VERTICES].nb_entry;
	if (!(tmp->value = malloc(tmp->size_alloc)))
		return (0);
	tmp->nb_entry = 0;
	return (1);
}

static int			get_file_2(FILE *f, t_obj *obj)
{
	char	str[MAX_STR_SIZE];
	char	*val;
	char	*tmp;

	while (fgets(str, MAX_STR_SIZE, f))
	{
		tmp = ft_strdup(str);
		val = strtok(tmp, " ");
		if (!ft_strcmp(val, "v"))
		{
			if (!get_vertice(str, obj->buffers + VERTICES))
			{
				ft_printf("ERROR get_vertice (%s)\n", str);
				return (0);
			}
		}
		else if (!ft_strcmp(val, "f"))
			get_face(str, obj->buffers + INDEXES);
		free(tmp);
	}
	return (1);
}

static int			get_files(FILE *f, t_obj *obj)
{
	char	str[MAX_STR_SIZE];
	char	*val;
	char	*tmp;

	while (fgets(str, MAX_STR_SIZE, f))
	{
		tmp = ft_strdup(str);
		val = strtok(tmp, " ");
		if (!ft_strcmp(val, "v"))
			obj->buffers[VERTICES].nb_entry += 3;
		else if (!ft_strcmp(val, "f"))
			obj->buffers[INDEXES].nb_entry += get_nb_index(str);
		free(tmp);
	}
	allocate_array(obj);
	fseek(f, 0, SEEK_SET);
	if (!get_file_2(f, obj))
		return (0);
	to_center(obj->buffers + VERTICES);
	return (1);
}

int					parse_file(t_obj *obj)
{
	FILE	*f;

	if (!(f = fopen(obj->file_name, "r")))
	{
		ft_printf("Error on file %s, %d, %s\n",
				obj->file_name, errno, strerror(errno));
		return (0);
	}
	if (!get_files(f, obj))
		return (0);
	fclose(f);
	return (1);
}

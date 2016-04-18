#include "parser.h"

static size_t	get_nb_index(char *str)
{
	GLuint	val[4];
	size_t	nb_val = 0;

	nb_val = sscanf(str, "f %u %u %u %u\n", val, val + 1, val + 2, val + 3);
	if (nb_val == 4)
		nb_val = 6;
	printf("nb val: %lu, str: %s\n", nb_val, str);
	return (nb_val);
}

static void		get_face(char *str, t_array *array)
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
		val[i]--;
		++i;
	}
	if (nb_val == 4)
	{
		i = array->nb_entry;
		ptr_uint[i++] = val[0];
		ptr_uint[i++] = val[1];
		ptr_uint[i++] = val[2];

		ptr_uint[i++] = val[0];
		ptr_uint[i++] = val[2];
		ptr_uint[i++] = val[3];
		array->size += sizeof(GLuint) * 6;
		array->nb_entry = i;
		return ;
	}
	i = 0;
	while (i < nb_val)
	{
		printf("%u ", val[i]);
		ptr_uint[array->nb_entry] = val[i];
		array->nb_entry++;
		++i;
	}
	printf("\n");
	array->size += sizeof(GLuint) * nb_val;
}

static int		get_vertice(char *str, t_array *array)
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
		printf("%f ", val[i]);
		ptr_float[array->nb_entry] = val[i];
		array->nb_entry++;
		++i;
	}
	printf("\n");
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
	printf("%lu, %lu\n", obj->buffers[INDEXES].nb_entry, obj->buffers[VERTICES].nb_entry);
	allocate_array(obj);
	fseek(f, 0, SEEK_SET);
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

int		parse_file(t_obj *obj)
{
	/*
	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
	};
	*/
	GLfloat colors[] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};
	/*
GLuint cube_elements[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};
	*/
	t_array	*tmp;
	FILE	*f;

	if (!(f = fopen(obj->file_name, "r")))
	{
		printf("Error on file %s, %d, %s\n", obj->file_name, errno, strerror(errno));
		return (0);
	}
	if (!get_files(f, obj))
		return (0);

	/*
	tmp = obj->buffers + VERTICES;
	tmp->value = malloc(sizeof(cube_vertices));
	tmp->nb_entry = 24;
	tmp->size = sizeof(cube_vertices);
	ft_memcpy(tmp->value, cube_vertices, sizeof(cube_vertices));
	*/

	tmp = obj->buffers + COLORS;
	tmp->value = malloc(sizeof(colors));
	tmp->nb_entry = 12;
	tmp->size = sizeof(colors);
	ft_memcpy(tmp->value, colors, sizeof(colors));

	/*
	tmp = obj->buffers + INDEXES;
	tmp->value = malloc(sizeof(cube_elements));
	tmp->nb_entry = 36;
	tmp->size = sizeof(cube_elements);
	ft_memcpy(tmp->value, cube_elements, sizeof(cube_elements));
	*/
	fclose(f);
	return (1);
}

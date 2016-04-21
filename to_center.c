#include "to_center.h"

static float	calc_m(t_array *array, size_t step, size_t offset)
{
	size_t	i;
	float	*v;
	float	max;
	float	min;
	char	first;

	i = offset;
	v = array->value;
	first = 1;
	while (i < array->nb_entry)
	{
		if (first)
		{
			min = v[i];
			max = v[i];
			first = 0;
		}
		if (v[i] < min)
			min = v[i];
		if (v[i] > max)
			max = v[i];
		i += step;
	}
	return (-((min + max) / 2.0f));
}

static void		apply_trans(t_array *array, float *trans, size_t size_trans)
{
	float	*v;
	size_t	i;
	size_t	j;

	v = array->value;
	i = 0;
	while (i < array->nb_entry)
	{
		j = 0;
		while (j < size_trans)
		{
			v[i + j] += trans[j];
			++j;
		}
		i += size_trans;
	}
}

void			to_center(t_array *array)
{
	float	cor[3];

	cor[0] = calc_m(array, 3, 0);
	cor[1] = calc_m(array, 3, 1);
	cor[2] = calc_m(array, 3, 2);
	apply_trans(array, cor, 3);
	printf("cor: %f, %f, %f\n", cor[0], cor[1], cor[2]);
}

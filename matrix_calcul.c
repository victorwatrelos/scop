#include "matrix_calcul.h"

float		*get_identity()
{
	float		*res;

	if (!(res = malloc(sizeof(float) * 16)))
		return (NULL);
	ft_bzero(res, sizeof(float) * 16);
	res[0] = 1;
	res[5] = 1;
	res[10] = 1;
	res[15] = 1;
	return (res);
}

void		display_matrix(float *m)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%.2ff ", m[i * 4 + j]);
			++j;
		}
		printf("\n");
		++i;
	}
}

float		*get_rot_matrix(float alpha)
{
	float	*res;
	float	cos_a;
	float	sin_a;

	if (!(res = get_identity()))
		return (NULL);
	cos_a = cos(alpha);
	sin_a = sin(alpha);
	res[0] = cos_a;
	res[2] = -sin_a;
	res[8] = sin_a;
	res[10] = cos_a;
	return (res);
}

float		*get_projection(float fovy, float aspect, float near, float far)
{
	float		f;
	float		*matrix;

	if (!(matrix = malloc(sizeof(float) * 16)))
		return (NULL);
	ft_bzero(matrix, sizeof(float) * 16);
	f = 1.0f / tanf(fovy / 2.0f);
    matrix[0]  = f / aspect;
    matrix[5]  = f;
    matrix[10] = (far + near)/ (near - far);
    matrix[11] = -1.0f;
    matrix[14] = 2.0f * (far * near) / (near - far);
	matrix[15] = 0.0f;
	return (matrix);
}

float		dot(float *v1, float *v2, size_t size)
{
	float		sum;
	size_t		i;

	sum = 0;
	i = 0;
	while (i < size)
	{
		sum += v1[i] * v2[i];
		++i;
	}
	return (sum);
}

float		*get_view_matrix(t_view *view)
{
	float		*res;
	int			i;
	int			j;

	res = malloc(sizeof(float) * 16);
	ft_bzero(res, sizeof(float) * 16);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i * 4 + j] = view->axis[i][j];
			++j;
		}
		++i;
	}
	res[12] = -dot(view->axis[0], view->eye_pos, 3);
	res[13] = -dot(view->axis[1], view->eye_pos, 3);
	res[14] = dot(view->axis[2], view->eye_pos, 3);
	res[15] = 1.f;
	return (res);
}

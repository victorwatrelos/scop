#include "matrix_calcul.h"

float		*mult(float *m1, float *m2)
{
	float	*res;

	if (!(res = malloc(sizeof(float) * 16)))
		return (NULL);
	res[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	res[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	res[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	res[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];
	res[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	res[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	res[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	res[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];
	res[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11]; 
	res[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	res[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	res[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];
	res[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	res[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	res[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	res[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
	return (res);
}

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

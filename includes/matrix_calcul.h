#ifndef MATRIX_CALCUL_H
# define MATRIX_CALCUL_H

# include "struct.h"
# include <stdlib.h>
# include <libft.h>
# include <math.h>

float	*get_view_matrix(t_view *view);
float	dot(float *v1, float *v2, size_t size);
float	*get_projection(float fovy, float aspect, float near, float far);
float	*mult(float *m1, float *m2);
void	view_matrix(float *m);
void	mult_vec(float *m, float *v);

#endif

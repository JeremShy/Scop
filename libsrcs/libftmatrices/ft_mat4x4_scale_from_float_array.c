#include <libftmatrices.h>

void	ft_mat4x4_scale_from_float_array(t_mat4x4 matrice, const float array[3])
{
	t_vec3	vector;

	ft_vec3_init(vector, array);
	ft_mat4x4_scale(matrice, vector);
}

#include <libftmatrices.h>

void	ft_mat4x4_scale_from_double_array(t_mat4x4 matrice, const double array[3])
{
	t_vec3	vector;

	ft_vec3_init(vector, array);
	ft_mat4x4_scale(matrice, vector);
}

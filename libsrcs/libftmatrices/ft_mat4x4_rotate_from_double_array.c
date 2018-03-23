#include <libftmatrices.h>

void	ft_mat4x4_rotate_from_double_array(t_mat4x4 matrice, double angle, const double array[3])
{
	t_vec3	vector;

	ft_vec3_init(vector, array);
	ft_mat4x4_rotate(matrice, angle, vector);
}

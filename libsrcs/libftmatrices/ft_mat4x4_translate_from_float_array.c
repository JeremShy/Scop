#include <libftmatrices.h>

void	ft_mat4x4_translate_from_float_array(t_mat4x4 matrice, const float array[3])
{
	t_vec3	vector;

	vector = ft_vec3_init(array);
	ft_mat4x4_translate(matrice, vector);
}

#include <libftmatrices.h>

void	ft_mat4x4_translate(t_mat4x4 m, const t_vec3 v)
{
	t_mat4x4	translation_matrix;

	ft_mat4x4_set_translation(translation_matrix, v);
	ft_mat4x4_mult(m, m, translation_matrix);
	
}

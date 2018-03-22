#include <libftmatrices.h>

void	ft_mat4x4_translate(t_mat4x4 m, const t_vec4 v)
{
	t_mat4x4	translation_matrix;

	ft_mat4x4_set_translation(translation_matrix, v);

	printf("Translation matrix: \n");
	ft_mat4x4_print(translation_matrix);
	printf("matrix: \n");
	ft_mat4x4_print(m);

	ft_mat4x4_mult(m, m, translation_matrix);

	printf("Result : \n");
	ft_mat4x4_print(m);
	
}

#include <libftmatrices.h>

void	ft_vec3_sub(t_vec3 dst, const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	copy;

	ft_vec3_copy(copy, v2);
	copy[0] *= -1;
	copy[1] *= -1;
	copy[2] *= -1;
	ft_vec3_add(dst, v1, copy);
}

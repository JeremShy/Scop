#include <libftmatrices.h>

void	ft_mat4x4_set_translation(t_mat4x4 m, const t_vec3 v)
{
	ft_mat4x4_set_identity(m);
	m[0][3] = v.x;
	m[1][3] = v.y;
	m[2][3] = v.z;
}

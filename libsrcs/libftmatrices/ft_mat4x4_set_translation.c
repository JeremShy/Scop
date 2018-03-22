#include <libftmatrices.h>

void	ft_mat4x4_set_translation(t_mat4x4 m, t_vec4 v)
{
	ft_mat4x4_set_identity(m);
	m[0][3] = v[0];
	m[1][3] = v[1];
	m[2][3] = v[2];
}

#include <libftmatrices.h>

double	ft_vec3_dot(const t_vec3 u, const t_vec3 v)
{
	return (u[0] * v[0] + u[1] * v[1] + u[2] * v[2]);
}

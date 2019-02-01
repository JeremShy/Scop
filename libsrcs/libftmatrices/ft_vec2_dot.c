#include <libftmatrices.h>

float	ft_vec2_dot(const t_vec2 u, const t_vec2 v)
{
	return (u.x * v.x + u.y * v.y);
}

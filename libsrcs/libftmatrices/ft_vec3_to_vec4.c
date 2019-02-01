#include <libftmatrices.h>

t_vec4	ft_vec3_to_vec4(const t_vec3 v)
{
	return ((t_vec4){v.x, v.y, v.z, 0});
}

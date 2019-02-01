#include <libftmatrices.h>

t_vec3	ft_vec4_to_vec3(const t_vec4 v)
{
	return ((t_vec3){v.x, v.y, v.z});
}

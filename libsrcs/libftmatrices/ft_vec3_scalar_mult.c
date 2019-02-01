#include <libftmatrices.h>

t_vec3	ft_vec3_scalar_mult(t_vec3 v, float f)
{
	return ((t_vec3){v.x * f, v.y * f, v.z * f});
}

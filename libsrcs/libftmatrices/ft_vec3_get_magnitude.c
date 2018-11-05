#include <libftmatrices.h>

float	ft_vec3_get_magnitude(const t_vec3 vector)
{
	return (sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]));
}

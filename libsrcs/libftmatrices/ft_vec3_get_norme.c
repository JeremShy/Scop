#include <libftmatrices.h>

float	ft_vec3_get_norme(const t_vec3 vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));
}

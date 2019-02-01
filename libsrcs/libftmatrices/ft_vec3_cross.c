#include <libftmatrices.h>

t_vec3		ft_vec3_cross(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	dst;

	dst.x = v1.y * v2.z - v1.z * v2.y;
	dst.y = v1.z * v2.x - v1.x * v2.z;
	dst.z = v1.x * v2.y - v1.y * v2.x;

	return (dst);
}

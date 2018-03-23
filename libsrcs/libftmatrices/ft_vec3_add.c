#include <libftmatrices.h>

void		ft_vec3_add(t_vec3 dst, const t_vec3 v1, const t_vec3 v2)
{
	dst[0] = v1[0] + v2[0];
	dst[1] = v1[1] + v2[1];
	dst[2] = v1[2] + v2[2];
}

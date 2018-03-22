#include <libftmatrices.h>

void	ft_vec3_copy(t_vec3 dst, const t_vec3 src)
{
	ft_memcpy(dst, src, sizeof(t_vec3));
}

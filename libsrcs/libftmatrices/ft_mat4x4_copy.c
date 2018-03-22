#include <libftmatrices.h>

void	ft_mat4x4_copy(t_mat4x4 dest, const t_mat4x4 src)
{
	ft_memcpy(dest, src, sizeof(t_mat4x4));
}

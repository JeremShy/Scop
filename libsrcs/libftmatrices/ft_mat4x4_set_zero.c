#include <libftmatrices.h>

void	ft_mat4x4_set_zero(t_mat4x4 m)
{
	ft_bzero(m, sizeof(t_mat4x4));
}

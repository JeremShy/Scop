#include <libftmatrices.h>

void	ft_vec4_init(t_vec4 vec, const float tab[4])
{
	vec[0] = tab[0];
	vec[1] = tab[1];
	vec[2] = tab[2];
	vec[3] = tab[3];
}

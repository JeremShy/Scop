#include <libftmatrices.h>

float	ft_vec2_get_norme(const t_vec2 vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y));
}

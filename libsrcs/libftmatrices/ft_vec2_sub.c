#include <libftmatrices.h>

t_vec2	ft_vec2_sub(t_vec2 v1, t_vec2 v2)
{
	return ((t_vec2){v1.x - v2.x, v1.y - v2.y});
}

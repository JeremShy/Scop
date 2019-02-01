#include <libftmatrices.h>

t_vec2	ft_vec2_get_normal(t_vec2 v)
{
	return ((t_vec2){-v.y, v.x});
}

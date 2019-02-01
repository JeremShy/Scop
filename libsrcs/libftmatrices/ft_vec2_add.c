#include <libftmatrices.h>

t_vec2		ft_vec2_add(const t_vec2 v1, const t_vec2 v2)
{
	t_vec2	dst;

	dst.x = v1.x + v2.x;
	dst.y = v1.y + v2.y;
	return (dst);
}

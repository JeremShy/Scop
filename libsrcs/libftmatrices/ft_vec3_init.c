#include <libftmatrices.h>

t_vec3	ft_vec3_init(const float tab[3])
{
	t_vec3	vec;

	vec.x = tab[0];
	vec.y = tab[1];
	vec.z = tab[2];
	return (vec);
}

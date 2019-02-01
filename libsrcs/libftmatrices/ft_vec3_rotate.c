#include <libftmatrices.h>

t_vec3	ft_vec3_rotate(t_vec3 vec, float angle, t_vec3 axis)
{
	t_mat4x4	rot;
	t_vec4		ret;

	ft_mat4x4_set_rotation(rot, angle, axis);
	ret = ft_mat4x4_mult_with_vec4(rot, (t_vec4){vec.x, vec.y, vec.z, 0});
	return ((t_vec3){ret.x, ret.y, ret.z});
}

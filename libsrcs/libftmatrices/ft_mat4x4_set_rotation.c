#include <libftmatrices.h>

void	ft_mat4x4_set_rotation(t_mat4x4 matrice, double angle, const t_vec3 axis)
{
	t_vec3	v;
	double	c;
	double	s;
	double	d;

	c = cos(degrees_to_radians(angle));
	s = sin(degrees_to_radians(angle));
	d = 1 - c;

	ft_vec3_copy(v, axis);
	ft_vec3_normalize(v);
	matrice[0][0] = v[0] * v[0] * d + c;
	matrice[0][1] = v[0] * v[1] * d - v[2] * s;
	matrice[0][2] = v[0] * v[2] * d + v[1] * s;
	matrice[0][3] = 0;
	matrice[1][0] = v[0] * v[1] * d + v[2] * s;
	matrice[1][1] = v[1] * v[1] * d + c;
	matrice[1][2] = v[1] * v[2] * d - v[0] * s;
	matrice[1][3] = 0;
	matrice[2][0] = v[0] * v[2] * d - v[1] * s;
	matrice[2][1] = v[1] * v[2] * d + v[0] * s;
	matrice[2][2] = v[2] * v[2] * d + c;
	matrice[2][3] = 0;
	matrice[3][0] = 0;
	matrice[3][1] = 0;
	matrice[3][2] = 0;
	matrice[3][3] = 1;
}

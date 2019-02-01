#include <libftmatrices.h>

void	ft_mat4x4_set_rotation(t_mat4x4 matrice, float angle, const t_vec3 axis)
{
	t_vec3	v;
	float	c;
	float	s;
	float	d;

	c = cos(degrees_to_radians(angle));
	s = sin(degrees_to_radians(angle));
	d = 1 - c;

	v = axis;
	ft_vec3_normalize(&v);
	matrice[0][0] = v.x * v.x * d + c;
	matrice[0][1] = v.x * v.y * d - v.z * s;
	matrice[0][2] = v.x * v.z * d + v.y * s;
	matrice[0][3] = 0;
	matrice[1][0] = v.x * v.y * d + v.z * s;
	matrice[1][1] = v.y * v.y * d + c;
	matrice[1][2] = v.y * v.z * d - v.x * s;
	matrice[1][3] = 0;
	matrice[2][0] = v.x * v.z * d - v.y * s;
	matrice[2][1] = v.y * v.z * d + v.x * s;
	matrice[2][2] = v.z * v.z * d + c;
	matrice[2][3] = 0;
	matrice[3][0] = 0;
	matrice[3][1] = 0;
	matrice[3][2] = 0;
	matrice[3][3] = 1;
}

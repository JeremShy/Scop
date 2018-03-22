#include <libftmatrices.h>

void	ft_vec3_normalize(t_vec3 vector)
{
	double	magnitude;

	magnitude = ft_vec3_get_magnitude(vector);
	vector[0] = vector[0] / magnitude;
	vector[1] = vector[1] / magnitude;
	vector[2] = vector[2] / magnitude;
}

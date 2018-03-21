#include <libftmatrices.h>

void	ft_mat4x4_mult_with_int(t_mat4x4 rez, t_mat4x4 m, int r)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			rez[i][j] = m[i][j] * r;
			j++;
		}
		i++;
	}
}

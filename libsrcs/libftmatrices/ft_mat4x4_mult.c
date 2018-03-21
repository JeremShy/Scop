#include <libftmatrices.h>

static void	compound_mult(t_mat4x4 m1, t_mat4x4 m2)
{
	printf("Detected compound mult.\n");
	t_mat4x4	tmp;

	ft_mat4x4_copy(tmp, m1);
	ft_mat4x4_mult(m1, tmp, m2);
}

static int32_t	get_res_at(t_mat4x4 a, t_mat4x4 b, int8_t i, int8_t j)
{
	int8_t	k;
	int32_t	sum;

	k = 0;
	sum = 0;
	while (k < 4)
	{
		sum += a[i][k] * b[k][j];
		k++;
	}
	return (sum);
}

void		ft_mat4x4_mult(t_mat4x4 ret, t_mat4x4 m1, t_mat4x4 m2)
{
	int8_t	i;
	int8_t	j;

	if (ret == m1)
		return (compound_mult(m1, m2));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret[i][j] = get_res_at(m1, m2, i, j);
			j++;
		}
		i++;
	}
}

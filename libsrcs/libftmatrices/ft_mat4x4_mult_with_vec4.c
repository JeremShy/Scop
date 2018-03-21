#include <libftmatrices.h>

static void	compound_mult(t_mat4x4 m1, t_vec4 vec)
{
	t_vec4 tmp;

	ft_vec4_init(tmp, vec);
	ft_mat4x4_mult_with_vec4(vec, m1, tmp);
}

static int	do_mult(t_mat4x4 m1, t_vec4 vec, int i)
{
	int	j;
	int	rez;

	j = 0;
	rez = 0;
	while (j < 4)
	{
		rez += m1[i][j] * vec[j];
		j++;
	}
	return (rez);
}

void		ft_mat4x4_mult_with_vec4(t_vec4 rez, t_mat4x4 m1, t_vec4 vec)
{
	int	i;

	if (rez == vec)
		return (compound_mult(m1, vec));
	i = 0;
	while (i < 4)
	{
		rez[i] = do_mult(m1, vec, i);
		i++;
	}
}

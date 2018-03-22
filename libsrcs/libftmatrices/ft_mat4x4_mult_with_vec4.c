#include <libftmatrices.h>

static void	compound_mult(const t_mat4x4 m1, t_vec4 rez) // Note:  vec == rez
{
	t_vec4 tmp;

	ft_vec4_init(tmp, rez);
	ft_mat4x4_mult_with_vec4(rez, m1, tmp);
}

static double	do_mult(const t_mat4x4 m1, const t_vec4 vec, int8_t i)
{
	int8_t	j;
	double	rez;

	j = 0;
	rez = 0.0;
	while (j < 4)
	{
		rez += m1[i][j] * vec[j];
		j++;
	}
	return (rez);
}

void		ft_mat4x4_mult_with_vec4(t_vec4 rez, const t_mat4x4 m1, const t_vec4 vec)
{
	int8_t	i;

	if (rez == vec)
		return (compound_mult(m1, rez));
	i = 0;
	while (i < 4)
	{
		rez[i] = do_mult(m1, vec, i);
		i++;
	}
}

#include <scop.h>

int8_t	get_three_floats(char *line, t_vec3 ret)
{
	char	**tab;
	int		i;

	tab = split_whitespace(line);
	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		if (i == 3 && tab[i][0] != '#')
			return (free_str_dtab(tab));
		if (check_float(tab[i]))
		{
			ret[i] = atof(tab[i]);
			if (ft_strchr(tab[i], '#') && i < 3)
				return (free_str_dtab(tab));
		}
		else
			return (free_str_dtab(tab));
		i++;
	}
	free_str_dtab(tab);
	return (1);
}

void	handle_v(char *line, t_obj *ret)
{
	t_vec3	v;

	debut_handle(&line, ret, 1);
	if (ret->error)
		return ;
	if (!get_three_floats(line, v))
	{
		ret->error = 1;
		return ;
	}
	ft_vec3_copy(ret->vertices[ret->vertices_nbr], v);
	ft_vec3_print(ret->vertices[ret->vertices_nbr]);
	ret->vertices_nbr++;
}

void	handle_vn(char *line, t_obj *ret)
{
	t_vec3	v;

	debut_handle(&line, ret, 2);
	if (ret->error)
		return ;
	if (!get_three_floats(line, v))
	{
		ret->error = 1;
		return ;
	}
	ft_vec3_copy(ret->normales[ret->normales_nbr], v);
	ft_vec3_print(ret->normales[ret->normales_nbr]);
	ret->normales_nbr++;
}

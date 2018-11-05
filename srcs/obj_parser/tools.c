#include <scop.h>

int	check_float(char *str)
{
	int	x;
	int	dot;

	x = 0;
	dot = 0;
	if (str[x] == '-' || str[x] == '+')
		str++;
	while (str[x] || x == 0)
	{
		if (x == 0 && !ft_isdigit(str[x]))
			return (0);
		if (str[x] == '.')
		{
			if (dot == 0)
				dot = 1;
			else
				return (0);
			x++;
		}
		else if (ft_isdigit(str[x]))
			x++;
		else if (str[x] == '#' && x != 0)
			return (1);
		else
			return (0);
	}
	return (1);
}

float			ft_atof(char *str)
{
	float		n;
	int			i;
	int			k;
	int			signe;

	i = 0;
	n = 0;
	k = 0;
	signe = 1;
	signe = (str[i] == '-') ? -signe : signe;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (str[i] > 47 && str[i] < 58)
	{
		n = n * 10 + (str[i++] - 48);
		if (str[i] == '.' || str[i] == ',')
			k = i++;
	}
	while (k != 0 && str[++k])
		signe = signe * 10;
	return (n / signe);
}

int8_t	free_str_dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

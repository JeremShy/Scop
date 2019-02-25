#include <scop.h>

static int	check_dot_exp(char *str, int *x, int *e, int *dot)
{
	if (str[*x] == '.')
	{
		if (*dot == 0)
			*dot = 1;
		else
			return (0);
		(*x)++;
		return (1);
	}
	else if (str[*x] == 'e' || str[*x] == 'E')
	{
		*dot = 1;
		if (*e == 0)
			*e = 1;
		else
			return (0);
		*x += str[*x + 1] == '-' || str[*x + 1] == '+' ? 2 : 1;
		return (1);
	}
	return (2);
}

int			check_float(char *str)
{
	int	x;
	int	dot;
	int e;
	int ret;

	x = 0;
	dot = 0;
	e = 0;
	if (str[x] == '-' || str[x] == '+')
		str++;
	while (str[x] || x == 0)
	{
		if (x == 0 && !ft_isdigit(str[x]))
			return (0);
		if ((ret = check_dot_exp(str, &x, &e, &dot)) == 0)
			return (0);
		else if (ret == 1)
			;
		else if (ft_isdigit(str[x]))
			x++;
		else
			return (str[x] == '#' && x != 0);
	}
	return (1);
}

float		ft_atof(char *str)
{
	int		entier;
	int		exp;
	int		curr;
	float	dec;

	entier = atoi(str);
	if (entier != 0)
		str += (int)log10(entier);
	else
		str++;
	if (*str == '.')
	{
		dec = 0;
		curr = 10;
		while (*(++str) >= 0x30 && *str <= 0x39)
		{
			dec += (*str - '0') / curr;
			curr /= 10;
		}
	}
	if (*str == 'e' || *str == 'E')
		exp = atoi(++str);
	dec = (entier > 0) ? (entier + dec) * pow(10, exp) :
	(entier - dec) * pow(10, exp);
	return (dec);
}

int8_t		free_str_dtab(char **tab)
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

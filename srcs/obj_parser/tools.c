#include <scop.h>

int	check_float(char *str)
{
	int	x;
	int	dot;
	int e;

	x = 0;
	dot = 0;
	e = 0;
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
		else if (str[x] == 'e' || str[x] == 'E')
		{
			dot = 1;
			if (e == 0)
				e = 1;
			else
				return (0);
			x += str[x + 1] == '-' || str[x + 1] == '+' ? 2 : 1;
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
	int entier;
	int exp;
	int curr;
	float dec;

	entier = atoi(str);
	if (entier != 0)
		str += (int)log10(entier);
	else
		str++;
	if (*str == '.')
	{
		str++;
		dec = 0;
		curr = 10;
		while (*str >= 0x30 && *str <= 0x39)
		{
			dec += (*str - '0') / curr;
			curr /= 10;
			str++;
		}
	}
	if (*str == 'e' || *str == 'E')
	{
		str++;
		exp = atoi(str);
	}
	dec = (entier > 0) ? (entier + dec) * pow(10, exp) : (entier - dec) * pow(10, exp);
	return (dec);
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

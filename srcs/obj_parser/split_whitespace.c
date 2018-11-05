#include <scop.h>

static int		ft_isspace(char car)
{
	if (car == '\t' || car == ' ')
		return (1);
	else
		return (0);
}

static int		ft_strcount(char const *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] != '\0' && s[i] != '#')
	{
		while (ft_isspace(s[i]) && s[i] != '\0' && s[i] != '#')
			i++;
		if (s[i] != '\0' && s[i] != '#')
			count++;
		while (!ft_isspace(s[i]) && s[i] != '\0' && s[i] != '#')
			i++;
	}
	return (count);
}

static int		poulet(size_t i, size_t j, char const *s)
{
	while (!ft_isspace(s[i + j]) && s[i + j] != '\0' && s[i + j] != '#')
		j++;
	return (j);
}

static	char	**ft_fln(char const *s, char **res, size_t *x)
{
	size_t	i;
	size_t	j;

	i = 0;
	*x = 0;
	while (s[i] != '\0' && s[i] != '#')
	{
		while (ft_isspace(s[i]) && s[i] != '\0' && s[i] != '#')
			i++;
		j = 0;
		j = poulet(i, j, s);
		if ((s[i + j] != '\0' && s[i + j] != '#') || !ft_isspace(s[i + j - 1]))
		{
			res[*x] = ft_strsub(s, i, j);
			*x = *x + 1;
		}
		i += j;
	}
	return (res);
}

char			**split_whitespace(char const *s)
{
	char	**res;
	size_t	x;

	res = malloc((ft_strcount(s) + 1) * sizeof(char*));
	if (!s || !res)
		return (NULL);
	if (ft_strcount(s) == 0)
	{
		res[0] = NULL;
		return (res);
	}
	res = ft_fln(s, res, &x);
	res[x] = NULL;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:20 by marnaud           #+#    #+#             */
/*   Updated: 2019/02/26 15:49:53 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

size_t		find_next_line(char *line)
{
	size_t	s;

	s = 0;
	while (*line && *line != '\xd' && *line != '\n')
	{
		line++;
		s++;
	}
	return (s);
}

int8_t		is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\xd')
		return (1);
	else
		return (0);
}

int			ignore_whitespaces(char **line)
{
	int i;

	i = 0;
	while (**line)
	{
		if (is_whitespace(**line))
		{
			(*line)++;
			i++;
		}
		else if (**line == '#')
		{
			while (**line && **line != '\n')
			{
				i++;
				(*line)++;
			}
			return (i);
		}
		else
			return (i);
	}
	return (i);
}

int			find_next_ignored_char(char *line)
{
	int		i;
	uint8_t escape;

	i = 0;
	escape = 0;
	while (line[i] && line[i] != '\n')
	{
		if (is_whitespace(line[i]) && !escape)
			return (i);
		if (escape)
			escape = 0;
		else if (line[i] == '\\')
			escape = 1;
		i++;
	}
	return (i);
}

int8_t		ignored_line(char *line)
{
	if (line[0] == '\0')
		return (1);
	else
		return (0);
}

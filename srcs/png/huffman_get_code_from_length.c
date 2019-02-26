/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:20 by magouin           #+#    #+#             */
/*   Updated: 2019/02/26 15:49:53 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <png.h>

static void	fill_bl_count(uint16_t *bl_count,
	struct s_length_code *length_code, size_t s)
{
	uint16_t	i;

	ft_bzero(bl_count, (MAX_BITS + 1) * sizeof(uint16_t));
	i = 0;
	while (i < s)
	{
		if (length_code[i].length != 0)
			bl_count[length_code[i].length]++;
		i++;
	}
}

static void	fill_next_code(uint16_t *next_code, uint16_t *bl_count)
{
	uint16_t	bits;
	uint16_t	code;

	code = 0;
	bits = 1;
	bl_count[0] = 0;
	while (bits <= MAX_BITS)
	{
		code = (code + bl_count[bits - 1]) << 1;
		next_code[bits] = code;
		bits++;
	}
}

void		fill_codes(uint16_t *next_code,
	struct s_length_code *length_codes, size_t s)
{
	size_t	i;

	i = 0;
	while (i < s)
	{
		if (length_codes[i].length != 0)
		{
			length_codes[i].code = next_code[length_codes[i].length];
			next_code[length_codes[i].length]++;
		}
		i++;
	}
}

void		get_code_from_lengths(struct s_length_code *length_codes, size_t s)
{
	uint16_t	bl_count[MAX_BITS + 1];
	uint16_t	next_code[MAX_BITS + 1];

	ft_bzero(bl_count, sizeof(bl_count));
	ft_bzero(next_code, sizeof(next_code));
	fill_bl_count(bl_count, length_codes, s);
	fill_next_code(next_code, bl_count);
	fill_codes(next_code, length_codes, s);
}

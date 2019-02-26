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

uint8_t	sub(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	return (data[i] + left(data, i, png_ihdr));
}

uint8_t	up(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	return (data[i] + prior(data, i, png_ihdr));
}

uint8_t	average(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	uint16_t	tmp_large;
	uint8_t		tmp;

	tmp_large = left(data, i, png_ihdr) + prior(data, i, png_ihdr);
	tmp = tmp_large >> 1;
	return (data[i] + tmp);
}

uint8_t	paeth(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	uint8_t	rez;

	rez = data[i] + paeth_predictor(left(data, i, png_ihdr),
		prior(data, i, png_ihdr), prior_left(data, i, png_ihdr));
	return (rez);
}

uint8_t	apply_filter(uint8_t filter, uint8_t *data,
	struct s_png_ihdr *png_ihdr, size_t i)
{
	if (filter == 0)
		return (data[i]);
	else if (filter == 1)
		return (sub(data, i, png_ihdr));
	else if (filter == 2)
		return (up(data, i, png_ihdr));
	else if (filter == 3)
		return (average(data, i, png_ihdr));
	else if (filter == 4)
		return (paeth(data, i, png_ihdr));
	else
		return (0);
}

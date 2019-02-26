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

#include <png.h>
#include <scop.h>

uint32_t		get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((int)b << 0) | ((int)g << 8) | ((int)r << 16) | ((int)a << 24));
}

void			dest_img_from_bpp(int bpp, uint8_t *src_img, uint32_t *dest_img)
{
	if (bpp == 4)
		*dest_img = get_color_code(*src_img,
			*(src_img + 1), *(src_img + 2),
			*(src_img + 3));
	if (bpp == 3)
		*dest_img = get_color_code(*src_img,
			*(src_img + 1), *(src_img + 2), 1);
	if (bpp == 2)
		*dest_img = get_color_code(*src_img,
			*src_img, *src_img, 1);
}

void			copy_source_in_img(struct s_png_ihdr *png_ihdr,
	uint8_t *src_img, uint32_t *dest_img)
{
	size_t		id_source;
	size_t		id_dest;
	size_t		y;
	size_t		x;

	id_source = 0;
	id_dest = 0;
	y = png_ihdr->height;
	while (y > 0)
	{
		x = 0;
		while (x < png_ihdr->width)
		{
			id_dest = x + (y - 1) * png_ihdr->width;
			if (id_source % (png_ihdr->width * png_ihdr->bpp + 1) == 0)
				id_source++;
			dest_img_from_bpp(png_ihdr->bpp,
				src_img + id_source, dest_img + id_dest);
			id_source += png_ihdr->bpp;
			x++;
		}
		y--;
	}
}

void			apply_all_filters(struct s_png_ihdr *png_ihdr,
	uint8_t *img_data)
{
	size_t	index_source;
	size_t	index_dest;
	size_t	source_size;
	uint8_t	current_filter;

	index_source = 0;
	index_dest = 0;
	source_size = png_ihdr->width * png_ihdr->height * png_ihdr->bpp +
	png_ihdr->height;
	while (index_source < source_size)
	{
		if (index_source % (png_ihdr->width * png_ihdr->bpp + 1) == 0)
		{
			current_filter = img_data[index_source];
			index_source++;
		}
		img_data[index_source] = apply_filter(current_filter, img_data,
			png_ihdr, index_source);
		index_source++;
	}
}

uint8_t			*get_compressed_data(void *addr, size_t file_size)
{
	struct s_chunk_hdr	*current_chunk;
	uint8_t				*compressed_data;
	size_t				i;

	i = 0;
	current_chunk = addr + 8;
	while (get_conv_32(&(current_chunk =
		get_next_chunk(current_chunk))->type) != IEND)
	{
		if (get_conv_32(&current_chunk->type) != IDAT)
			return ((void*)print_and_ret("NOT IDAT", addr, file_size, NULL));
		i += get_conv_32(&current_chunk->length);
	}
	if (!(compressed_data = malloc(i)))
		return ((void*)print_and_ret("Memory error", addr, file_size, NULL));
	current_chunk = addr + 8;
	i = 0;
	while (get_conv_32(&(current_chunk =
		get_next_chunk(current_chunk))->type) != IEND)
	{
		ft_memcpy(compressed_data + i, (void*)current_chunk + 8,
			get_conv_32(&current_chunk->length));
		i += get_conv_32(&current_chunk->length);
	}
	return (compressed_data);
}

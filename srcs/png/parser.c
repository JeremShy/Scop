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

static uint8_t	initialize_values(void **addr, const char *name,
	off_t *file_size, struct s_png_ihdr *png_ihdr)
{
	if (!(*addr = init_png_parser(name, file_size)))
		return (0);
	if (*file_size < 8 || get_conv_64(*addr) != 0x89504E470D0A1A0Al)
		return (print_and_ret("Invalid signature", *addr, *file_size, NULL));
	if (!check_and_read_ihdr(*addr, png_ihdr))
		return (print_and_ret(NULL, *addr, *file_size, NULL));
	return (1);
}

int8_t			create_image(t_d *data, uint16_t id, uint16_t w, uint16_t h)
{
	data->max_img_id++;
	data->imgs[id].w = w;
	data->imgs[id].h = h;
	if (!(data->imgs[id].data = malloc(4 * sizeof(float) * w * h)))
		return (0);
	return (1);
}

uint8_t			create_image_from_png(t_d *data, int id_img,
	const char *name)
{
	struct s_png_ihdr	png_ihdr;
	void				*addr;
	off_t				file_size;
	uint8_t				*img_data;
	uint8_t				*compressed_data;

	if (!initialize_values(&addr, name, &file_size, &png_ihdr))
		return (0);
	if (!(compressed_data = get_compressed_data(addr, file_size)))
		return (0);
	munmap(addr, file_size);
	if (!(img_data = malloc(png_ihdr.width * png_ihdr.height *
		png_ihdr.bpp + png_ihdr.height)))
		return (print_and_ret("Memory error 2", NULL, file_size,
			compressed_data));
		png_inflate((void*)compressed_data, img_data);
	free(compressed_data);
	create_image(data, id_img, png_ihdr.width, png_ihdr.height);
	apply_all_filters(&png_ihdr, img_data);
	copy_source_in_img(&png_ihdr, img_data, (uint32_t*)data->imgs[id_img].data);
	free(img_data);
	return (1);
}

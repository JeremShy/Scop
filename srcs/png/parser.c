#include <png.h>
#include <scop.h>

static uint8_t	*get_compressed_data(void *addr, size_t file_size)
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

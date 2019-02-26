#include <png.h>
#include <scop.h>

uint32_t	get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((int)b << 0) | ((int)g << 8) | ((int)r << 16) | ((int)a << 24));
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
			if (png_ihdr->bpp == 4)
				dest_img[id_dest] = get_color_code(src_img[id_source],
					src_img[id_source + 1], src_img[id_source + 2],
					src_img[id_source + 3]);
			if (png_ihdr->bpp == 3)
				dest_img[id_dest] = get_color_code(src_img[id_source],
					src_img[id_source + 1], src_img[id_source + 2], 1);
			if (png_ihdr->bpp == 2)
				dest_img[id_dest] = get_color_code(src_img[id_source],
					src_img[id_source], src_img[id_source], 1);
			printf("%hhu %hhu %hhu\n", src_img[id_source], src_img[id_source + 1], src_img[id_source + 2]);
			id_source += png_ihdr->bpp;
			x++;
		}
		y--;
	}
}

static void		apply_all_filters(struct s_png_ihdr *png_ihdr,
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

int8_t	create_image(t_d *data, uint16_t id, uint16_t w, uint16_t h)
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

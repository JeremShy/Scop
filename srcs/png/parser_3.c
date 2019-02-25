#include <png.h>
#include <scop.h>

uint32_t		get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((int)b << 0) | ((int)g << 8) | ((int)r << 16) | ((int)a << 24));
}

void			fill_line(struct s_png_ihdr *png_ihdr, uint8_t *src_img,
	uint32_t *dest_img, size_t id_dest)
{
	size_t		id_source;

	id_source = 0;
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
	id_source += png_ihdr->bpp;
}

void			copy_source_in_img(struct s_png_ihdr *png_ihdr,
	uint8_t *src_img, uint32_t *dest_img)
{
	size_t		y;
	size_t		x;
	size_t		id_dest;

	y = png_ihdr->height + 1;
	while (--y > 0)
	{
		x = -1;
		while (++x < png_ihdr->width)
		{
			id_dest = x + (y - 1) * png_ihdr->width;
			fill_line(png_ihdr, src_img, dest_img, id_dest);
		}
	}
}

void		apply_all_filters(struct s_png_ihdr *png_ihdr,
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

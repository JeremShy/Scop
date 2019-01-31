#include <scop.h>
#include <png.h>

void		clamp(int32_t *point, int32_t min, int32_t max)
{
	*point < min ? (*point = min) : 0;
	*point > max ? (*point = max) : 0;
}

static uint64_t	average_color(uint32_t *color, uint32_t nb)
{
	uint64_t rez;

	color[0] /= nb;
	color[1] /= nb;
	color[2] /= nb;
	color[3] /= nb;
	rez = color[3] << 24;
	rez += color[2] << 16;
	rez += color[1] << 8;
	rez += color[0];
	return (rez);
}

static uint64_t	get_color_pixel(uint8_t *first_pix, uint32_t w,
	t_ivec2 inter_x, t_ivec2 inter_y)
{
	uint32_t	c[4];
	int			nb;
	int			x;
	int			y;

	nb = 0;
	ft_bzero(c, sizeof(c));
	x = inter_x.x;
	y = inter_y.x;
	while (y <= inter_y.y)
	{
		c[0] += first_pix[x * 4 + y * 4 * w + 0];
		c[1] += first_pix[x * 4 + y * 4 * w + 1];
		c[2] += first_pix[x * 4 + y * 4 * w + 2];
		c[3] += first_pix[x * 4 + y * 4 * w + 3];
		if (x == inter_x.y)
		{
			x = inter_x.x;
			y++;
		}
		else
			x++;
		nb++;
	}
	return (average_color(c, nb));
}

static uint32_t	get_pixel_color(t_ivec2 size, uint32_t *src_img,
	t_vec2 *count, t_vec2 *ratio)
{
	t_ivec2		inter_x;
	t_ivec2		inter_y;
	uint64_t	rez;

	inter_x = (t_ivec2){roundf(count->x - (ratio->x / 2)),
		roundf(count->x + (ratio->x / 2 - .001))};
	inter_y = (t_ivec2){roundf(count->y - (ratio->y / 2)),
		roundf(count->y + (ratio->y / 2 - .001))};
	clamp(&inter_x.x, 0, size.x - 1);
	clamp(&inter_x.y, 0, size.x - 1);
	clamp(&inter_y.x, 0, size.y - 1);
	clamp(&inter_y.y, 0, size.y - 1);
	rez = get_color_pixel((uint8_t *)src_img, size.x, inter_x, inter_y);
	return (rez);
}

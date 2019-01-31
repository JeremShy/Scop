#include <scop.h>
#include <png.h>

uint8_t	left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	if (i % (png_ihdr->bpp * png_ihdr->width + 1) < png_ihdr->bpp + 1)
		return (0);
	else
		return (data[i - png_ihdr->bpp]);
}

uint8_t	prior(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	if (i < png_ihdr->bpp * png_ihdr->width + 1)
		return (0);
	else
		return (data[i - (png_ihdr->bpp * png_ihdr->width + 1)]);
}

uint8_t	prior_left(uint8_t *data, size_t i, struct s_png_ihdr *png_ihdr)
{
	if (i % (png_ihdr->bpp * png_ihdr->width + 1) < png_ihdr->bpp + 1)
		return (0);
	else if (i < png_ihdr->bpp * png_ihdr->width + 1)
		return (0);
	else
		return (data[i - (png_ihdr->bpp + png_ihdr->bpp *
			png_ihdr->width + 1)]);
}

uint8_t	paeth_predictor(int a, int b, int c)
{
	int32_t	p;
	int32_t	pa;
	int32_t	pb;
	int32_t	pc;

	p = a + b - c;
	pa = abs(p - a);
	pb = abs(p - b);
	pc = abs(p - c);
	if (pa <= pb && pa <= pc)
		return (a);
	else if (pb <= pc)
		return (b);
	else
		return (c);
}

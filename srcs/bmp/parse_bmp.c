#include <bmp.h>
#include <scop.h>
#include <stdio.h>

static uint32_t	get_color_code(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((int)b << 0) | ((int)g << 8) | ((int)r << 16) | ((int)a << 24));
}

void	*read_bmp(const char *pathname, off_t *size)
{
	int				fd;
	struct stat		buf;
	void			*ptr;

	if ((fd = open(pathname, O_RDONLY)) == -1)
	{
		printf("On peut pas ouvrir : %s\n", pathname);
		return (NULL);
	}
	if ((fstat(fd, &buf)) == -1)
	{
		printf("On peut pas ouvrir : %s\n", pathname);
		close(fd);
		return (NULL);
	}
	*size = buf.st_size;
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("On peut pas ouvrir : %s\n", pathname);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (ptr);
}

void	*parse_bmp(const char *pathname, t_img *img)
{
	t_header	header;
	t_info		dib;
	void		*ptr;
	off_t		size;

	if (!(ptr = read_bmp(pathname, &size)))
		return (NULL);
	header = *(t_header *)ptr;
	dib = *(t_info *)(ptr + 14);

	if (dib.size != 12)
	{
		printf("Mauvais format de bmp\n");
		return (NULL);
	}
	if (dib.bpp != 24)
	{
		printf("Oups, je n'accepte que les bmp couleur 24 bits\n");
		return (NULL);
	}

	img->w = dib.w;
	img->h = dib.h;
	return (ptr);
}

void		fill_img(t_img *img, void *ptr, uint32_t *dest_img)
{
	int 		x;
	int 		y;

	x = 0;
	while (x < img->w)
	{
		y = img->h - 1;
		while (y >= 0)
		{
			dest_img[(x) + ((y) * img->w)] = (get_color_code(*(uint8_t *)(ptr + 1 + 36), *(uint8_t *)(ptr + 36), *(uint8_t *)(ptr + 2 + 36), 0));
			ptr += 3;
			y--;
		}
		x++;
	}
}

// void		fill_img(t_img *img, void *ptr, uint32_t *dest_img)
// {
// 	int 		x;
// 	int 		y;

// 	y = 0;
// 	while (y < img->h)
// 	{
// 		x = img->w;
// 		while (x > 0)
// 		{
// 			dest_img[(y) + ((x - 1) * img->h)] = (get_color_code(*(uint8_t *)(ptr + 1 + 36), *(uint8_t *)(ptr + 36), *(uint8_t *)(ptr + 2 + 36), 0));
// 			ptr += 3;
// 			x--;
// 		}
// 		y++;
// 	}
// }

int			create_img(const char *pathname, t_img *img)
{
	void		*ptr;

	printf("Trying to read %s:\t", pathname);
	if (!(ptr = parse_bmp(pathname, img)))
	{
		return (0);
	}

	if (!(img->data = (uint8_t *)malloc(sizeof(uint8_t) * (img->w * img->h * 4))))
	{
		return (0);
	}
	fill_img(img, ptr, (uint32_t*)img->data);
	return (1);
}

uint8_t			create_image_from_bmp(t_d *data, int id_img,
	const char *pathname)
{
	if (!(create_img(pathname, &data->imgs[id_img])))
	{
		printf("Error\n");
		return (0);
	}
	printf("✔\n");
	return (1);
}
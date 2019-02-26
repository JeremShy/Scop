#include <bmp.h>
#include <scop.h>
#include <stdio.h>

void	*read_bmp(const char *pathname, off_t *size)
{
	int				fd;
	struct stat		buf;
	void			*ptr;

	if ((fd = open(pathname, O_RDONLY)) == -1)
		return (NULL);
	if ((fstat(fd, &buf)) == -1)
	{
		close(fd);
		return (NULL);
	}
	*size = buf.st_size;
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
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
	printf("header\n");
	printf("\tmagic:\t%hd\n", header.magic);
	printf("\tsize\t%d\n", header.size);
	printf("\treserved1\t%hd\n", header.reserved1);
	printf("\treserved2\t%hd\n", header.reserved2);
	printf("\toffset\t%d\n", header.offset);
	printf("DIB header\n");
	printf("\tsize:\t%d\n", dib.size);
	printf("\tw\t%hd\n", dib.w);
	printf("\th\t%hd\n", dib.h);
	printf("\tcolor\t%hd\n", dib.color);
	printf("\tbpp\t%hd\n", dib.bpp);

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

int		fill_img(const char *pathname, t_img *img)
{
	void		*ptr;
	int 		n;

	if (!(ptr = parse_bmp(pathname, img)))
		return (0);

	if (!(img->data = (uint8_t *)malloc(sizeof(uint8_t) * (img->w * img->h * 4))))
		return (0);
	n = 0;
	while (n < (img->w * img->h) * 4)
	{
		img->data[n] = *(uint8_t *)(ptr + 36);
		img->data[n + 1] = *(uint8_t *)(ptr + 1 + 36);
		img->data[n + 2] = *(uint8_t *)(ptr + 2 + 36);
		img->data[n + 3] = 0;
		n += 4;
		ptr += 3;
	}
	return (1);
}

uint8_t			create_image_from_bmp(t_d *data, int id_img,
	const char *pathname)
{
	if (!(fill_img(pathname, &data->imgs[id_img])))
		return (0);
	return (1);
}
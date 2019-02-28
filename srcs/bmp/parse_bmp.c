/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:49:03 by marnaud           #+#    #+#             */
/*   Updated: 2019/02/28 12:49:06 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bmp.h>
#include <scop.h>

static void		*read_bmp(const char *pathname, off_t *size)
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

static void		*parse_bmp(const char *pathname, t_img *img)
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
		return (NULL);
	if (dib.bpp != 24)
		return (NULL);
	img->w = dib.w;
	img->h = dib.h;
	return (ptr);
}

static void		fill_img(t_img *img, void *ptr, uint32_t *dest_img)
{
	int	x;
	int	y;

	x = 0;
	while (x < img->w)
	{
		y = 0;
		while (y < img->h)
		{
			dest_img[y + (x * img->h)] = (((int)(*(uint8_t *)(ptr + 2 + 36))
				<< 0) | ((int)(*(uint8_t *)(ptr + 36))
				<< 8) | ((int)(*(uint8_t *)(ptr + 1 + 36))
				<< 16) | ((int)0 << 24));
			ptr += 3;
			y++;
		}
		x++;
	}
}

static int		create_img(const char *pathname, t_img *img)
{
	void		*ptr;

	ft_putstr("Trying to read :\t");
	ft_putstr((char *)pathname);
	if (!(ptr = parse_bmp(pathname, img)))
	{
		ft_putstr("Not possible to read :\t");
		ft_putstr((char *)pathname);
		return (0);
	}
	if (!(img->data = (uint8_t *)malloc(sizeof(uint8_t)
		* (img->w * img->h * 4))))
		return (0);
	fill_img(img, ptr, (uint32_t*)img->data);
	return (1);
}

uint8_t			create_image_from_bmp(t_d *data, int id_img,
	const char *pathname)
{
	if (!(create_img(pathname, &data->imgs[id_img])))
	{
		ft_putstr("\tError\n");
		return (0);
	}
	ft_putstr("\t✔\n");
	return (1);
}

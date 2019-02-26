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

#include <scop.h>
#include <png.h>

static uint8_t		get_bytes_per_pixel(struct s_png_ihdr *png_ihdr)
{
	if (png_ihdr->color_type == 0)
		return (png_ihdr->bdp >> 3);
	else if (png_ihdr->color_type == 2)
		return (3 * (png_ihdr->bdp >> 3));
	else if (png_ihdr->color_type == 6)
		return (4 * (png_ihdr->bdp >> 3));
	else
		return (0);
}

void				*init_png_parser(const char *name, off_t *size)
{
	int				fd;
	struct stat		buf;
	void			*addr;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		printf("Error couldn't open %s\n", name);
		return (NULL);
	}
	if ((fstat(fd, &buf)) == -1)
	{
		printf("Error couldn't open %s\n", name);
		close(fd);
		return (NULL);
	}
	*size = buf.st_size;
	if ((addr = mmap(NULL, buf.st_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		printf("Error couldn't open %s\n", name);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (addr);
}

struct s_chunk_hdr	*get_next_chunk(void *current_chunk)
{
	struct s_chunk_hdr	*ret;

	ret = current_chunk;
	ret = (void*)ret + get_conv_32(&ret->length) + 12;
	while (get_conv_32(&ret->type) != IEND && (ret->type & 0x20))
		ret = (void*)ret + get_conv_32(&ret->length) + 12;
	return (ret);
}

int64_t				print_and_ret(const char *str, void *addr, off_t file_size,
	uint8_t *compressed_data)
{
	if (str)
		ft_putendl_fd((char*)str, 2);
	munmap(addr, file_size);
	free(compressed_data);
	return (0);
}

uint8_t				check_and_read_ihdr(void *addr, struct s_png_ihdr *png_ihdr)
{
	struct s_chunk_hdr	chunk_header;

	chunk_header.length = get_conv_32(addr + 8);
	chunk_header.type = get_conv_32(addr + 12);
	if (chunk_header.type != IHDR || chunk_header.length != 13)
	{
		ft_putendl_fd("Invalid first chunk.", 2);
		return (0);
	}
	*png_ihdr = *((struct s_png_ihdr*)(addr + 16));
	if (png_ihdr->color_type == 3 || png_ihdr->color_type == 4
		|| png_ihdr->bdp != 8)
	{
		ft_putendl_fd("Error : Can't handle palettes or 16bit images. ", 2);
		return (0);
	}
	png_ihdr->width = get_conv_32(&png_ihdr->width);
	png_ihdr->height = get_conv_32(&png_ihdr->height);
	png_ihdr->bpp = get_bytes_per_pixel(png_ihdr);
	return (1);
}

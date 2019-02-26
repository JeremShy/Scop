#include "tga.h"
#include <stdio.h>

void	*read_tga(const char *pathname, off_t *size)
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

void	parse_tga(const char *pathname)
{
	t_header	h;
	void		*ptr;
	off_t		size;
	uint8_t		*ii;
	uint8_t		cmd_offset;

	int			n;

	if (!(ptr = read_tga(pathname, &size)))
		return ;
	h = *(t_header *)ptr;
	h.cms = *(t_cms *)(ptr + 3);
	h.is = *(t_is *)(ptr + 8);
	printf("Taille du champ contenant l'ID de l'image:\t%hhd\nIndique si une table des couleurs est présente:\t%hhd\nType de compression et de couleurs:\t%hhd\n", h.idl, h.cmt, h.it);
	printf("Décrit la table des couleurs\n");
	printf("\tFirst entry index:\t%hd\n", h.cms.fei);
	printf("\tColor map length:\t%hd\n", h.cms.cml);
	printf("\tColor map entry size:\t%hhd\n", h.cms.cmes);
	printf("Dimensions de l'image et son format\n");
	printf("\tX-origin:\t%hd\n", h.is.xo);
	printf("\tY-origin:\t%hd\n", h.is.yo);
	printf("\tImage width:\t%hd\n", h.is.iw);
	printf("\tImage height:\t%hd\n", h.is.ih);
	printf("\tPixel depth:\t%hhd\n", h.is.pd);
	printf("\tImage descriptor:\t%hhd\n", h.is.id);

	if (h.idl)
	{
		if (!(ii = (uint8_t *)malloc(sizeof(uint8_t) * h.idl)))
			return ;
		ii = *((sizeof(uint8_t) * h.idl) *)(ptr + sizeof(t_header));
		printf("Image ID:\t%s\n", ii);
	}

	if (h.cmt)
	{
		printf("Il faut creer une table de couleur de taille: %hd, qui commencre en: %hd, avec un nombre de bit par pixel de: %hhd\n", h.cms.fei, h.cms.cml, h.cms.cmes);
	}

}

int		main(int ac, char const **av)
{
	if (ac > 1)
	{
		parse_tga(av[1]);
	}
	return 0;
}
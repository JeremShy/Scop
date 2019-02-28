/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 12:52:47 by marnaud           #+#    #+#             */
/*   Updated: 2019/02/28 12:52:48 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/mman.h>

typedef struct	s_header
{
	uint16_t	magic;
	uint32_t	size;
	uint16_t	reserved1;
	uint16_t	reserved2;
	uint32_t	offset;
}				t_header;

typedef struct	s_info
{
	uint32_t	size;
	uint16_t	w;
	uint16_t	h;
	uint16_t	color;
	uint16_t	bpp;
}				t_info;

#endif

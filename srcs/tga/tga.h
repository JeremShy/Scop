#ifndef PNG_H
# define PNG_H

# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
#include <sys/mman.h>

typedef struct	s_cms
{
	uint16_t	fei;	
	uint16_t	cml;	
	uint8_t		cmes;	
}				t_cms;

typedef struct	s_is
{
	uint16_t	xo;
	uint16_t	yo;
	uint16_t	iw;
	uint16_t	ih;
	uint8_t		pd;
	uint8_t		id;
}				t_is;

typedef struct	s_header
{
	uint8_t	idl;
	uint8_t	cmt;
	uint8_t	it;
	t_cms	cms;
	t_is	is;
}				t_header;

#endif